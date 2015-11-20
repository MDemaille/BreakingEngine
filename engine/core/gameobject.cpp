#include "engine/core/gameobject.h"
#include "engine/core/component.h"

GameObject::GameObject(GameObject *parent) : QObject(parent)
{
    setObjectName("GameObject");

}

GameObject::GameObject(QString name, GameObject *parent) : QObject(parent)
{
    setObjectName(name);
}

GameObject::~GameObject()
{

}
