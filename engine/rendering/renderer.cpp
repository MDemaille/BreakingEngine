#include "renderer.h"
#include "engine/core/camera.h"
#include "engine/core/gameobject.h"
#include "engine/core/component.h"
#include "engine/opengl/bspmanager.h"

Renderer::Renderer(GameObject* parent) : Component(parent)
{
    setObjectName("rendering/Renderer");

}

Renderer::~Renderer() {

}

void Renderer::render()
{
    if(m_breaking_shader_program==nullptr)
        m_breaking_shader_program = BSPManager::Instance()->getDefaultBreakingShaderProgram();

    //Bind Shader
    m_breaking_shader_program->bind();

    //Compute matrix
    QMatrix4x4 projection;
    QMatrix4x4 view;
    view = Camera::main->viewMatrix();
    projection = Camera::main->projectionMatrix();
    //Link matrix to shader (compute mvp)
    m_breaking_shader_program->computeWith(projection,view,modelMatrix());
    //Draw the content in model view
    renderContent();

    //Release Shader
    m_breaking_shader_program->release();
}
