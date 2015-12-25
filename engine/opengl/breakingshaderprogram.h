#ifndef BREAKINGSHADERPROGRAM_H
#define BREAKINGSHADERPROGRAM_H

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

class BreakingShaderProgram
{
    QOpenGLShaderProgram* m_opengl_shader_program;

    QVector4D mainColor;

    int m_uniform_modelview;
    int m_uniform_projection;
    int m_uniform_color;

public:
    BreakingShaderProgram();
    virtual void start();
    virtual ~BreakingShaderProgram();
    virtual void computeWith(QMatrix4x4 projection, QMatrix4x4 view, QMatrix4x4 model);
    virtual void bind();
    virtual void release();
    virtual bool addShader(QOpenGLShader *shader);
};

#endif // BREAKINGSHADERPROGRAM_H
