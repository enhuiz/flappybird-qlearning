#ifndef PIPE_HPP
#define PIPE_HPP

#include <random>

#include "../engine/gameobject.hpp"
#include "../engine/eg.hpp"

namespace enhuiz
{
namespace flappybird
{
class Pipe : public engine::GameObject
{
  public:
    Pipe(int x, const std::shared_ptr<Pipe> &passivePipe = nullptr) : mPassivePipe(passivePipe)
    {
        mIsCollider = true;
        mBounds = SDL_Rect{0, 0, 48, 320};

        mTransform.position.x = x;
        mSprite.atlasName = "flappyBird";
        mSprite.name = mPassivePipe ? "pipe_down" : "pipe_up";
        mVelocity = 1.5;
        shuffleY();
    }

    void fixedUpdate()
    {
        mTransform.position.x -= mVelocity;
        if (mTransform.position.x < -160)
        {
            mTransform.position.x += 160 * 3;
            shuffleY();
        }
    }

    void stop()
    {
        mVelocity = 0;
    }

    int getScore(int x)
    {
        int ret = 0;
        if (x > mTransform.position.x - 11)
        {
            ret = mScore;
            mScore = 0;
        }
        return ret;
    }

    bool isDown()
    {
        return mPassivePipe != nullptr;
    }

  private:
    void shuffleY()
    {
        if (mPassivePipe)
        {
            mScore = 1;
            mTransform.position.y = randFloat(-280, -100);
            mPassivePipe->mTransform.position.y = mTransform.position.y + 415;
        }
    }

    float randFloat(float l, float r)
    {
        static std::random_device rd;
        static std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(l, r);

        return dist(mt);
    }

  private:
    float mVelocity;
    std::shared_ptr<Pipe> mPassivePipe;

    int mScore = 0;
};
}
}

#endif