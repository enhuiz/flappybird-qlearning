#include "game.hpp"

namespace enhuiz
{
namespace flappybird
{
Game::Game() : mScore(0), sharedThis(std::shared_ptr<Game>(this))
{
    mEG = std::unique_ptr<engine::EG>(new engine::EG("flappyBird", 288, 512, 0));

    mEG->addAtlas("flappyBird", "../res/flappyAtlas/atlas.png", "../res/flappyAtlas/atlas.txt");

    mBird = std::make_shared<Bird>();
    mBird->setGame(sharedThis);

    play();
}

void Game::play(float delay)
{
    if (mAboutToPlay)
        return;
    mAboutToPlay = true;
    mEG->callAfter(delay, [&]() {
        mScore = 0;

        mBackgrounds.clear();
        for (int i = 0; i < 2; ++i)
        {
            mBackgrounds.push_back(std::make_shared<Background>(288 * i));
        }

        mLands.clear();
        for (int i = 0; i < 2; ++i)
        {
            mLands.push_back(std::make_shared<Land>(336 * i));
        }

        mScoreDigits.clear();
        for (int i = 0; i < 5; ++i)
        {
            mScoreDigits.push_back(std::make_shared<Digit>());
        }

        mPipes.clear();
        for (int i = 0; i < 3; ++i)
        {
            auto up = std::make_shared<Pipe>(300 + 150 * i);
            auto down = std::make_shared<Pipe>(300 + 150 * i, up);
            mPipes.push_back(up);
            mPipes.push_back(down);
        }

        mEG->clear();
        for (auto bg : mBackgrounds)
        {
            mEG->addGameObject(bg);
        }
        for (auto pipe : mPipes)
        {
            mEG->addGameObject(pipe);
        }
        for (auto land : mLands)
        {
            mEG->addGameObject(land);
        }
        for (auto digit : mScoreDigits)
        {
            mEG->addGameObject(digit);
        }

        mEG->addGameObject(mBird);
        updateScoreDisplay();

        mAboutToPlay = false;
    });
}

void Game::gameover()
{
    for (auto bg : mBackgrounds)
    {
        bg->stop();
    }
    for (auto pipe : mPipes)
    {
        pipe->stop();
    }
    for (auto land : mLands)
    {
        land->stop();
    }
    play(0);
}

void Game::run()
{
    mEG->run();
}

void Game::updateScoreDisplay()
{
    for (auto digit : mScoreDigits)
    {
        digit->setActive(false);
    }

    int tmp = mScore;
    int n = 0;

    while (tmp)
    {
        int d = tmp % 10;
        mScoreDigits[n]->setValue(d);
        ++n;
        tmp /= 10;
    }

    int offset = n % 2 == 0 ? 144 - n * 12 : 132 - n / 2 * 12;

    for (int i = 0; i < n; ++i)
    {
        mScoreDigits[i]->setActive(true);
        mScoreDigits[i]->setPosition(offset + (n - 1 - i) * 24);
    }

    if (n == 0)
    {
        mScoreDigits[0]->setActive(true);
        mScoreDigits[0]->setValue(0);
        mScoreDigits[0]->setPosition(132);
    }
}

void Game::updateScore(int posX)
{
    for (const auto &pipe : mPipes)
    {
        mScore += pipe->getScore(posX);
    }
    updateScoreDisplay();
}

engine::Vector3 Game::getNearestPipePosition(engine::Vector3 pos) const
{
    engine::Vector3 ret{1 << 20, 0, 0};

    for (const auto &pipe : mPipes)
    {
        if (pipe->isDown())
            continue;

        auto rect = pipe->toRect();

        if (pos.x < rect.x + rect.w && ret.x > rect.x + rect.w)
        {
            ret = engine::Vector3{rect.x + rect.w, rect.y, 0};
        }
    }
    return ret;
}
}
}