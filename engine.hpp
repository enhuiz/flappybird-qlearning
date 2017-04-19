#include <string>
#include <thread>
#include <memory>
#include <algorithm>
#include <list>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.hpp"

namespace enhuiz
{
class Engine
{
  private:
    struct sdl_deleter
    {
        void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
        void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
        void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
        void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
    };


  public:
    struct Transform
    {
        math::Vector3 position;
    };

    class Sprite
    {
      public:
        Sprite(std::string filename)
        {
            mSurface = std::unique_ptr<SDL_Surface, sdl_deleter>(
                IMG_Load(filename.c_str()),
                sdl_deleter());

            if (mSurface)
            {
                std::cerr << "Surface not loaded" << std::endl;
                return;
            }
            else 
            {
                std::cerr << "Surface loaded" << std::endl;
            }
        }

        void setRenderer(const std::shared_ptr<SDL_Renderer> &renderer)
        {
            mTexture = std::shared_ptr<SDL_Texture>(
                SDL_CreateTextureFromSurface(renderer.get(), mSurface.get()),
                sdl_deleter());

            if (mTexture == nullptr)
            {
                std::cerr << "Texture not loaded" << std::endl;
            }

            SDL_QueryTexture(mTexture.get(), NULL, NULL, &mWidth, &mHeight);
        }

        std::shared_ptr<SDL_Texture> getTexture()
        {
            return mTexture;
        }

        int getWidth()
        {
            return mWidth;
        }

        int getHeight()
        {
            return mHeight;
        }

      private:
        std::unique_ptr<SDL_Surface, sdl_deleter> mSurface;
        std::shared_ptr<SDL_Texture> mTexture;
        int mWidth, mHeight;
    };

    class GameObject
    {
      public:
        GameObject() = default;
        ~GameObject() {}

        void setActive(bool active)
        {
            mActive = active;
        }

        bool isActive()
        {
            return mActive;
        }

        void setSprite(std::shared_ptr<Sprite> sprite)
        {
            mSprite = sprite;
        }

        void render()
        {
            if (mRenderer.expired())
                return;

            if (mSprite != nullptr)
            {
                SDL_Rect rect{
                    transform.position.x,
                    transform.position.y,
                    mSprite->getWidth(),
                    mSprite->getHeight(),
                };
                SDL_RenderCopy(mRenderer.lock().get(), mSprite->getTexture().get(), nullptr, &rect);
            }
        }

        void setRenderer(const std::shared_ptr<SDL_Renderer> &renderer)
        {
            mRenderer = std::weak_ptr<SDL_Renderer>(renderer);
            mSprite->setRenderer(renderer);
        }

        virtual void update()
        {
        }

        virtual void start()
        {
        }

      protected:
        bool mActive = true;
        std::string name = "";
        Transform transform;

        std::shared_ptr<Sprite> mSprite;
        std::weak_ptr<SDL_Renderer> mRenderer;
    };

  public:
    Engine(std::string title, int width, int height) : mScreen(title, width, height)
    {
    }

    void update()
    {
        for (auto gameObject : mGameObjects)
        {
            if (gameObject->isActive())
            {
                gameObject->update();
            }
        }
    }

    void render()
    {
        SDL_RenderClear(mScreen.getRenderer().get());
        for (auto gameObject : mGameObjects)
        {
            if (gameObject->isActive())
            {
                gameObject->render();
            }
        }
        SDL_RenderPresent(mScreen.getRenderer().get());
    }

    void pollEvent()
    {
        SDL_PollEvent(mScreen.getEvent().get());
        if (mScreen.getEvent()->type == SDL_QUIT)
        {
            mRunning = false;
        }
    }

    void run()
    {
        mRunning = true;
        while (mRunning)
        {
            pollEvent();
            update();
            render();
        }
    }

    void addGameObject(const std::shared_ptr<GameObject> &gameObject)
    {
        mGameObjects.push_back(gameObject);
        gameObject->setRenderer(mScreen.getRenderer());
        gameObject->start();
    }

    void removeGameObject(const std::shared_ptr<GameObject> &gameObject)
    {
        mGameObjects.remove(gameObject);
    }

  private:
    bool mRunning = false;
    std::list<std::shared_ptr<GameObject>> mGameObjects;
    Screen mScreen;
};
}