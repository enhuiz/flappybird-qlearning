#include "game.hpp"

namespace enhuiz
{
namespace flappybird
{
Game::Game() : mScore(0)
{
    mEG = std::unique_ptr<engine::EG>(new engine::EG("flappyBird", 288, 512));

    mEG->addAtlas("flappyBird", "../res/flappyAtlas/atlas.png", "../res/flappyAtlas/atlas.txt");

    for (int i = 0; i < 2; ++i)
    {
        mBackgrounds.push_back(std::make_shared<Background>(288 * i));
    }

    for (int i = 0; i < 2; ++i)
    {
        mLands.push_back(std::make_shared<Land>(336 * i));
    }

    for (int i = 0; i < 5; ++i)
    {
        mScoreDigits.push_back(std::make_shared<Digit>());
    }

    mBird = std::make_shared<Bird>();
    mBird->setGame(std::shared_ptr<Game>(this));

    play();
}

void Game::play()
{
    mEG->callAtNextEndOfFrame([&]() {
        mEG->clear();
        for (auto bg : mBackgrounds)
        {
            mEG->addGameObject(bg);
        }
        for (auto land : mLands)
        {
            mEG->addGameObject(land);
        }
        for (auto digit : mScoreDigits)
        {
            mEG->addGameObject(digit);
        }
        updateScoreDisplay();
        mEG->addGameObject(mBird);
    });
}

void Game::gameover()
{
    play();
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

void Game::addScore()
{
    ++mScore;
    updateScoreDisplay();
}
}
}