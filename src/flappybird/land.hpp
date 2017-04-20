#ifndef LAND_HPP
#define LAND_HPP

#include "../engine/gameobject.hpp"

namespace enhuiz
{
namespace flappybird
{
class Land : public engine::GameObject
{
  public:
    Land(int x)
    {
        mTag = "land";
        mIsCollider = true;
        mBounds = SDL_Rect{0, 0, 336, 112};

        mTransform.position.x = x;
        mTransform.position.y = 400;
    }

    void start()
    {
        mSprite.atlasName = "flappyBird";
        mSprite.name = "land";
        mVelocity = 1.5;
    }

    void fixedUpdate()
    {
        mTransform.position.x -= mVelocity;
        if (mTransform.position.x < -336)
        {
            mTransform.position.x += 336 * 2;
        }
    }

    void stop()
    {
        mVelocity = 0;
    }

  private:
    float mVelocity;
};
}
}
#endif