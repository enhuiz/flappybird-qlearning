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
        isCollider = true;
        mTransform.position.x = x;
        mTransform.position.y = 400;
    }

    void start()
    {
        mSprite.atlasName = "flappyBird";
        mSprite.name = "land";
        velocity = 1;
    }

    void fixedUpdate()
    {
        mTransform.position.x -= velocity;
        if (mTransform.position.x < -336)
        {
            mTransform.position.x += 336 * 2;
        }
    }

  private:
    float velocity;
    float pos;
};
}
}
#endif