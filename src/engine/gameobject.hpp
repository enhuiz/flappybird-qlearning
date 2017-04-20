#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL2/SDL.h>

#include "sprite.hpp"
#include "transform.hpp"

namespace enhuiz
{
namespace engine
{
class EG;
class GameObject
{
  friend class EG;

public:
  GameObject() = default;
  ~GameObject() {}

  void setActive(bool active) { mActive = active; }
  bool isActive() { return mActive; }
  std::string getTag() { return mTag; }
  // const Sprite &getSprite() const { return mSprite; }
  const Transform &getTransform() { return mTransform; }

  virtual void update() {}
  virtual void start() {}
  virtual void fixedUpdate() {}
  virtual void onCollide(std::shared_ptr<GameObject> other){};

  SDL_Rect toRect()
  {
    return SDL_Rect{
        static_cast<int>(mTransform.position.x + mBounds.x),
        static_cast<int>(mTransform.position.y + mBounds.y),
        static_cast<int>(mBounds.w),
        static_cast<int>(mBounds.h)};
  }

protected:
  bool mActive = true;
  bool mIsCollider = false;

  std::string mName = "";
  std::string mTag = "";

  Transform mTransform;
  std::shared_ptr<EG> mEG;

  SDL_Rect mBounds;

  Sprite mSprite;
};
}
}

#endif