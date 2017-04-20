#include <iostream>
#include "bird.hpp"

namespace enhuiz
{
namespace flappybird
{

void Bird::start()
{
    mIsCollider = true;
    mBounds = SDL_Rect{11, 17, 25, 15};

    mTransform.position.x = 35;
    mTransform.position.y = 20;
    mSprite.atlasName = "flappyBird";
    mSprite.name = "bird0_0";
    mVelocity = 0;
    mFrameCount = 0;
    mAnimateState = 0;
    mAlive = true;
    mOnTheGround = false;
}

void Bird::update()
{
    if (mEG->getEvent()->type == SDL_KEYDOWN && mEG->getEvent()->key.keysym.sym == SDLK_SPACE && mAlive)
    {
        mVelocity = -8;
    }
}

void Bird::fixedUpdate()
{
    if (!mOnTheGround)
    {
        mVelocity = std::min(mVelocity + 0.6f, 10.0f);
    }

    mTransform.position.y += mVelocity;

    if (toRect().y < 0)
    {
        mTransform.position.y -= mVelocity;
    }

    if (mFrameCount > 10)
    {
        mFrameCount = 0;
        ++mAnimateState;
        mAnimateState %= 3;
        mSprite.name = "bird0_";
        mSprite.name.push_back('0' + mAnimateState);
    }
    ++mFrameCount;

    mGame->updateScore(toRect().x);
}

void Bird::setGame(const std::shared_ptr<Game> &game)
{
    mGame = game;
}

void Bird::onCollide(std::shared_ptr<GameObject> other)
{
    if (other->getTag() == "land")
    {
        mOnTheGround = true;
        mVelocity = 0;
    }
    else
    {
        mVelocity = std::max(mVelocity, 0.0f);
    }
    mAlive = false;
    mGame->gameover();
}
}
}