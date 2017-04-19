#include "game.hpp"

namespace enhuiz
{
namespace flappybird
{
Game::Game()
{
    eg = std::unique_ptr<engine::EG>(new engine::EG("flappyBird", 288, 512));

    eg->addAtlas("flappyBird", "../res/flappyAtlas/atlas.png", "../res/flappyAtlas/atlas.txt");

    bgs.clear();
    bgs.push_back(std::make_shared<BackGround>(0));
    bgs.push_back(std::make_shared<BackGround>(288));

    lands.clear();
    lands.push_back(std::make_shared<Land>(0));
    lands.push_back(std::make_shared<Land>(336));

    bird = std::make_shared<Bird>();
    bird->setGame(std::shared_ptr<Game>(this));
    play();
}

void Game::play()
{
    eg->callAtNextEndOfFrame([&]() {
        eg->clear();
        for (auto bg : bgs)
        {
            eg->addGameObject(bg);
        }
        for (auto land : lands)
        {
            eg->addGameObject(land);
        }
        eg->addGameObject(bird);
    });
}

void Game::gameover()
{
    play();
}

void Game::run()
{
    eg->run();
}
}
}