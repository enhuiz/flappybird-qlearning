#ifndef BIRD_HPP
#define BIRD_HPP

#include "../engine/gameobject.hpp"
#include "../engine/eg.hpp"
#include "game.hpp"

namespace enhuiz
{
namespace flappybird
{
class Game;
class Bird : public engine::GameObject
{
public:
  void start();
  void update();
  void fixedUpdate();
  void onCollide(std::shared_ptr<GameObject> other);
  void setGame(const std::shared_ptr<Game> &game);

private:
  float mVelocity;
  int mFrameCount;
  int mAnimateState;
  std::shared_ptr<Game> mGame;
  bool mAlive;
  bool mOnTheGround;
};
}
}
#endif