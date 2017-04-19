#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

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

  // const Sprite &getSprite() const { return mSprite; }
  // const Transform &getTransform() { return mTransform; }

  virtual void update() {}
  virtual void start() {}
  virtual void fixedUpdate() {}

  virtual void onCollide(std::shared_ptr<GameObject> other){};

protected:
  bool mActive = true;
  bool isCollider = false;

  std::string mName = "";
  Transform mTransform;

  std::shared_ptr<EG> mEG;

  Sprite mSprite;
};
}
}

#endif