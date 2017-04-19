#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "../engine/eg.hpp"
#include "bird.hpp"
#include "background.hpp"
#include "land.hpp"
#include "digit.hpp"

namespace enhuiz
{
namespace flappybird
{
class Bird;
class Digit;
class Game
{
public:
  Game();
  void play();
  void gameover();
  void run();
  void addScore();
  void updateScoreDisplay();

private:
  std::shared_ptr<Bird> mBird;
  std::list<std::shared_ptr<Background>> mBackgrounds;
  std::list<std::shared_ptr<Land>> mLands;
  std::vector<std::shared_ptr<Digit>> mScoreDigits;

  std::unique_ptr<engine::EG> mEG;

  int mScore = 0;
};
}
}
#endif