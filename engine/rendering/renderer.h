#ifndef RENDERER_H
#define RENDERER_H

#include "engine/core/gameobject.h"
#include "engine/core/component.h"
#include "engine/core/transform.h"
#include <QMatrix4x4>
#include "engine/opengl/breakingshaderprogram.h"

class Renderer : public virtual Component
{
    BreakingShaderProgram* m_breaking_shader_program=nullptr;
public:
    Renderer(GameObject* parent=0);

    virtual ~Renderer();

    virtual QMatrix4x4 modelMatrix() {
        QMatrix4x4 model;
        model.setToIdentity();
        model.scale(gameObject()->transform()->scaling);
        model.rotate(gameObject()->transform()->rotation);
        model.translate(gameObject()->transform()->position);
        return model;
    }

    virtual void renderContent() = 0;
    virtual void render();
};

#endif // RENDERER_H
