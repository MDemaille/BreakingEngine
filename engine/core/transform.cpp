#include "engine/core/transform.h"


Transform::Transform(GameObject* parent) : Component(parent)
{
  setObjectName("core/Transform");
  position.setX(0);
  position.setY(0);
  position.setZ(0);
  scaling.setX(1);
  scaling.setY(1);
  scaling.setZ(1);
}

Transform::~Transform()
{

}
