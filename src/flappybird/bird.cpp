#include <iostream>
#include "bird.hpp"

namespace enhuiz
{
namespace flappybird
{

void Bird::start()
{
    isCollider = true;
    mTransform.position.x = 30;
    mTransform.position.y = 20;
    mSprite.atlasName = "flappyBird";
    mSprite.name = "bird0_0";
    velocity = 0;
    frameCount = 0;
    animateState = 0;
}

void Bird::update()
{
    if (mEG->getEvent()->type == SDL_KEYDOWN && mEG->getEvent()->key.keysym.sym == SDLK_SPACE)
    {
        velocity = -11;
    }
}

void Bird::fixedUpdate()
{
    velocity = std::min(velocity + 0.75f, 6.5f);
    mTransform.position.y += velocity;
    mTransform.position.y = std::max(0.0f, mTransform.position.y);

    if (frameCount > 10)
    {
        frameCount = 0;
        ++animateState;
        animateState %= 3;
        mSprite.name = "bird0_";
        mSprite.name.push_back('0' + animateState);
    }
    mGame->addScore();
    ++frameCount;
}

void Bird::setGame(const std::shared_ptr<Game> &game)
{
    mGame = game;
}

void Bird::onCollide(std::shared_ptr<GameObject> other)
{
    std::cerr << " bump" << std::endl;
    velocity = 0;
    mGame->gameover();
}
}
}