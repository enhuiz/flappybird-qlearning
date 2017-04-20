#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "../engine/eg.hpp"

#include "bird.hpp"
#include "background.hpp"
#include "land.hpp"
#include "digit.hpp"
#include "pipe.hpp"

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
  void play(float delay = 0);
  void gameover();
  void run();
  void updateScore(int posX);
  void updateScoreDisplay();
  engine::Vector3 getNearestPipePosition(engine::Vector3 pos) const;

private:
  std::shared_ptr<Bird> mBird;
  std::list<std::shared_ptr<Background>> mBackgrounds;
  std::list<std::shared_ptr<Land>> mLands;
  std::vector<std::shared_ptr<Digit>> mScoreDigits;
  std::list<std::shared_ptr<Pipe>> mPipes;

  std::unique_ptr<engine::EG> mEG;

  std::shared_ptr<Game> sharedThis;

  int mScore = 0;
  bool mAboutToPlay = false;
};
}
}
#endif