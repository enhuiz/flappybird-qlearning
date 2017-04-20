#include <iostream>
#include "bird.hpp"

namespace enhuiz
{
namespace flappybird
{

Bird::Bird() : mQL(new model::QL(2, 0.8, 0.8))
{
    mQLearning = true;
}

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
    if (mEG->getEvent()->type == SDL_KEYDOWN && mEG->getEvent()->key.keysym.sym == SDLK_SPACE && mAlive && !mQLearning)
    {
        jump();
    }
}

void Bird::jump()
{
    mVelocity = -8;
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

    // Q-learning Stuff
    if (mQLearning && mAlive)
    {
        reward(1);

        static std::random_device rd;
        static std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(0, 1);

        mAction = dist(mt) < 1 ? mQL->getArgMax(getState()) : static_cast<int>(dist(mt) * 2);
        if (mAction == 1)
        {
            jump();
        }
    }
}

std::string Bird::getState(int resolution)
{
    auto pos = mGame->getNearestPipePosition(mTransform.position);

    std::stringstream ss;
    ss << static_cast<int>(pos.x - mTransform.position.x) / resolution * resolution << "," << static_cast<int>(pos.y - mTransform.position.y) / resolution * resolution;

    return ss.str();
}

void Bird::reward(float r)
{
    auto currState = getState();
    mQL->reward(mPrevState, currState, mAction, r);
    mPrevState = currState;
}

void Bird::setGame(const std::shared_ptr<Game> &game)
{
    mGame = game;
}

void Bird::onCollide(std::shared_ptr<GameObject> other)
{
    if (mAlive && mQLearning)
    {
        reward(-100);
    }
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