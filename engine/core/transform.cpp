#include "engine/core/transform.h"


Transform::Transform(GameObject* parent) : Component(parent)
{
  setObjectName("core/Transform");
}

Transform::~Transform()
{

}
