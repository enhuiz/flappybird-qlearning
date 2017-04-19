#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "../engine/gameobject.hpp"

namespace enhuiz
{
namespace flappybird
{
class BackGround : public engine::GameObject
{
  public:
    BackGround(int x)
    {
        mTransform.position.x = x;
    }

    void start()
    {
        mSprite.atlasName = "flappyBird";
        mSprite.name = "bg_day";
        velocity = 1;
    }

    void fixedUpdate()
    {
        mTransform.position.x -= velocity;
        if (mTransform.position.x < -288)
        {
            mTransform.position.x += 288 * 2;
        }
    }

  private:
    float velocity;
    float pos;
};
}
}
#endif