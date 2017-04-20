#ifndef BIRD_HPP
#define BIRD_HPP

#include "../engine/gameobject.hpp"
#include "../engine/eg.hpp"

#include "../model/ql.hpp"

#include "game.hpp"

namespace enhuiz
{
namespace flappybird
{
class Game;
class Bird : public engine::GameObject
{
public:
  Bird();
  void start();
  void update();
  void fixedUpdate();
  void onCollide(std::shared_ptr<GameObject> other);
  void setGame(const std::shared_ptr<Game> &game);

private:
  void jump();
  void reward(float r);
  std::string getState(int resolution = 10);

private:
  float mVelocity;
  int mFrameCount;
  int mAnimateState;
  std::shared_ptr<Game> mGame;
  bool mAlive;
  bool mOnTheGround;

  bool mQLearning = false;

  std::unique_ptr<model::QL> mQL;

  std::string mPrevState;
  int mAction = 0;
};
}
}
#endif