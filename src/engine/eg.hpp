#ifndef EG_HPP
#define EG_HPP

#include <string>
#include <list>
#include <map>
#include <chrono>

#include "screen.hpp"
#include "gameobject.hpp"
#include "atlas.hpp"
#include "timer.hpp"

namespace enhuiz
{
namespace engine
{

class EG
{
    friend class GameObject;

  public:
    EG(std::string title, int width, int height, float fixedUpdateDuration = 0.01666666f) : mScreen(std::unique_ptr<Screen>(new Screen(title, width, height))),
                                                                                            mEvent(std::make_shared<SDL_Event>()),
                                                                                            mFixedUpdateDuration(fixedUpdateDuration),
                                                                                            sharedThis(std::shared_ptr<EG>(this)) {}
    void update()
    {
        for (auto gameObject : mGameObjects)
        {
            if (gameObject->mActive)
            {
                gameObject->update();
            }
        }
    }

    void fixedUpdate()
    {
        for (auto gameObject : mGameObjects)
        {
            if (gameObject->mActive)
            {
                gameObject->fixedUpdate();
            }
        }

        // collision
        for (auto goit1 = mGameObjects.begin(); goit1 != mGameObjects.end(); ++goit1)
        {
            for (auto goit2 = goit1; goit2 != mGameObjects.end(); ++goit2)
            {
                if (goit1 != goit2)
                {
                    auto go1 = *goit1;
                    auto go2 = *goit2;
                    if (go1->mIsCollider && go2->mIsCollider)
                    {
                        if (isOverlapped(go1, go2))
                        {
                            callAtEndOfNextFrame([=]() {
                                go1->onCollide(go2);
                                go2->onCollide(go1);
                            });
                        }
                    }
                }
            }
        }
    }

    void render()
    {
        SDL_RenderClear(mScreen->getRenderer().get());
        for (auto gameObject : mGameObjects)
        {
            if (gameObject->mActive)
            {
                render(gameObject);
            }
        }
        SDL_RenderPresent(mScreen->getRenderer().get());
    }

    void pollEvent()
    {
        SDL_PollEvent(mEvent.get());
        if (mEvent->type == SDL_QUIT)
        {
            mRunning = false;
        }
    }

    void run()
    {
        mRunning = true;
        while (mRunning)
        {
            timer.tick();

            pollEvent();

            update();

            mFixedUpdateDurationPool += timer.getDeltaTime();
            if (mFixedUpdateDurationPool > mFixedUpdateDuration)
            {
                fixedUpdate();
                mFixedUpdateDurationPool = 0;
            }

            render();

            // end of frame
            endOfFrameDelegates();
        }
    }

    void endOfFrameDelegates()
    {
        int size = mEndOfFrameDelegates.size();
        for (int i = 0; i < size; ++i)
        {
            auto pair = mEndOfFrameDelegates.front();
            mEndOfFrameDelegates.pop_front();
            if (pair.first < 0)
            {
                pair.second();
            }
            else
            {
                pair.first -= timer.getDeltaTime();
                mEndOfFrameDelegates.push_back(pair);
            }
        }
    }

    void addAtlas(std::string name, std::string imagepath, std::string descpath)
    {
        mAtlasByName[name] = std::unique_ptr<Atlas>(new Atlas(imagepath, descpath, mScreen->getRenderer()));
    }

    void addGameObject(const std::shared_ptr<GameObject> &gameObject)
    {
        mGameObjects.push_back(gameObject);

        gameObject->mEG = sharedThis;
        gameObject->start();
    }

    void removeGameObject(const std::shared_ptr<GameObject> &gameObject)
    {
        mGameObjects.remove(gameObject);
    }

    void clear()
    {
        mGameObjects.clear();
    }

    std::shared_ptr<SDL_Event> getEvent()
    {
        return mEvent;
    }

    void callAtEndOfNextFrame(std::function<void()> delegate)
    {
        callAfter(0, delegate);
    }

    void callAfter(float duration, std::function<void()> delegate)
    {
        mEndOfFrameDelegates.push_back(std::pair<float, std::function<void()>>(duration, delegate));
    }

  private:
    void render(const std::shared_ptr<GameObject> &gameObject) const
    {
        auto position = gameObject->mTransform.position;
        auto sprite = gameObject->mSprite;
        auto srcrect = mAtlasByName.at(sprite.atlasName)->getRect(sprite.name);

        SDL_Rect destrect{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            srcrect.w,
            srcrect.h,
        };

        SDL_RenderCopy(mScreen->getRenderer().get(),
                       mAtlasByName.at(sprite.atlasName)->getTexture().get(),
                       &srcrect,
                       &destrect);
    }

    bool isOverlapped(const std::shared_ptr<GameObject> &go1, const std::shared_ptr<GameObject> &go2) const
    {
        SDL_Rect rect1 = go1->toRect();
        SDL_Rect rect2 = go2->toRect();

        bool noHorizontal = rect1.x + rect1.w <= rect2.x || rect1.x >= rect2.x + rect2.w;
        bool noVertical = rect1.y + rect1.h <= rect2.y || rect1.y >= rect2.y + rect2.h;

        return !noHorizontal && !noVertical;
    }

  private:
    bool mRunning = false;
    float mFixedUpdateDuration;
    float mFixedUpdateDurationPool;
    Timer timer;

    std::map<std::string, std::unique_ptr<Atlas>> mAtlasByName;

    std::string currentSceneName;

    std::unique_ptr<Screen> mScreen;
    std::shared_ptr<SDL_Event> mEvent;

    std::list<std::shared_ptr<GameObject>> mGameObjects;
    std::list<std::pair<float, std::function<void()>>> mEndOfFrameDelegates;

    std::shared_ptr<EG> sharedThis;
};
}
}

#endif