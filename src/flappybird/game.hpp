#ifndef GAME_HPP
#define GAME_HPP

#include "../engine/eg.hpp"
#include "bird.hpp"
#include "background.hpp"
#include "land.hpp"

namespace enhuiz
{
namespace flappybird
{
class Bird;
class Game
{
public:
  Game();
  void play();
  void gameover();
  void run();

private:
  std::shared_ptr<Bird> bird;
  std::list<std::shared_ptr<BackGround>> bgs;
  std::list<std::shared_ptr<Land>> lands;

  std::unique_ptr<engine::EG> eg;
};
}
}
#endif