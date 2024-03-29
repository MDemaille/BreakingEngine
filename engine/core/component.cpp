#include "engine/core/component.h"
#include "engine/core/gameobject.h"


Component::Component(GameObject *parent): QObject(parent)
{
    setObjectName("core/Component");
}

Component::~Component() {

}

GameObject *Component::gameObject()
{
    QObject* pt = parent();

    return dynamic_cast<GameObject*>(pt);
}
