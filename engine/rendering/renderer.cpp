#include "renderer.h"
#include "engine/core/gameobject.h"
#include "engine/core/component.h"

Renderer::Renderer(GameObject* parent) : Component(parent)
{
    setObjectName("rendering/Renderer");

}

Renderer::~Renderer() {

}
