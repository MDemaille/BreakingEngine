#include "bspmanager.h"
#include <QOpenGLShader>
QString BSPManager::defaultShaderName = "BreakingShader";


BSPManager::BSPManager()
{
    BreakingShaderProgram* bsp = new BreakingShaderProgram();
    m_shaders[BSPManager::defaultShaderName] = bsp;


    //Default shader
    QOpenGLShader* vertex_shader = new QOpenGLShader(QOpenGLShader::Vertex);
    vertex_shader->compileSourceFile(":/resources/shaders/breaking.vs");
    QOpenGLShader* fragment_shader = new QOpenGLShader(QOpenGLShader::Fragment);
    fragment_shader->compileSourceFile(":/resources/shaders/breaking.fs");
    bsp->addShader(vertex_shader);
    bsp->addShader(fragment_shader);
    bsp->start();
}

BSPManager::~BSPManager()
{
    foreach(QString name, m_shaders.keys()) {
        BreakingShaderProgram* bsp = m_shaders[name];
        m_shaders.remove(name);
        delete bsp;
    }
}

