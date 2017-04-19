#ifndef DIGIT_HPP
#define DIGIT_HPP

#include <sstream>

#include "../engine/gameobject.hpp"

namespace enhuiz
{
namespace flappybird
{
class Digit : public engine::GameObject
{
  public:
    Digit()
    {
        mSprite.atlasName = "flappyBird";
        mTransform.position.y = 40;
    }

    void setPosition(int x)
    {
        mTransform.position.x = x;
    }

    void setValue(int val)
    {
        val %= 10;
        std::stringstream ss;
        ss << "font_0" << val + 48;

        mSprite.name = ss.str();
    }
};
}
}
#endif