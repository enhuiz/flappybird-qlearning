#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "../engine/gameobject.hpp"

namespace enhuiz
{
namespace flappybird
{
class Background : public engine::GameObject
{
  public:
    Background(int x)
    {
        mTransform.position.x = x;
    }

    void start()
    {
        mSprite.atlasName = "flappyBird";
        mSprite.name = "bg_day";
        mVelocity = 0.7;
    }

    void fixedUpdate()
    {
        mTransform.position.x -= mVelocity;
        if (mTransform.position.x < -288)
        {
            mTransform.position.x += 288 * 2;
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