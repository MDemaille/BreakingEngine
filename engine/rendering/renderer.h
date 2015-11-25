#ifndef RENDERER_H
#define RENDERER_H

#include "engine/core/component.h"

class Renderer : public virtual Component
{
public:
    Renderer(GameObject* parent=0);
    virtual ~Renderer();

    virtual void render() = 0;
};

#endif // RENDERER_H
