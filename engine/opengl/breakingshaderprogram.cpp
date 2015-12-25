#include "breakingshaderprogram.h"

BreakingShaderProgram::BreakingShaderProgram()
{
    mainColor = QVector4D(1.0f,1.0f,1.0f,1.0f);
    m_opengl_shader_program = new QOpenGLShaderProgram();
    m_opengl_shader_program->create();
}

BreakingShaderProgram::~BreakingShaderProgram() {

    delete m_opengl_shader_program;
}

void BreakingShaderProgram::start()
{
    if(!m_opengl_shader_program->link())
    {
        qDebug() << "linking error";
        exit(-100);
    }


    m_uniform_modelview = m_opengl_shader_program->uniformLocation("modelViewMatrix");
    if(m_uniform_modelview==-1)
        qDebug() << "modelViewError:"<< m_uniform_modelview;
    m_uniform_projection = m_opengl_shader_program->uniformLocation("projectionMatrix");
    if(m_uniform_projection==-1)
        qDebug() << "projectionError"<< m_uniform_projection;

    m_uniform_color = m_opengl_shader_program->uniformLocation("color");
    if(m_uniform_color==-1)
        qDebug() << "colorError";
}


void BreakingShaderProgram::computeWith(QMatrix4x4 projection, QMatrix4x4 view, QMatrix4x4 model) {
    QMatrix4x4 modelViewMatrix = view * model;
    //QMatrix3x3 worldNormalMatrix = model.normalMatrix();
    //QMatrix3x3 normalMatrix = modelViewMatrix.normalMatrix();
    //QMatrix4x4 mvpMatrix = projection * modelViewMatrix;
    //qDebug() << "mvpMatrix:"<<mvpMatrix;
    m_opengl_shader_program->setUniformValue(m_uniform_modelview, modelViewMatrix);
    m_opengl_shader_program->setUniformValue(m_uniform_projection, projection);
    m_opengl_shader_program->setUniformValue(m_uniform_color, mainColor);
}

void BreakingShaderProgram::bind() {
    m_opengl_shader_program->bind();
}

void BreakingShaderProgram::release() {
    m_opengl_shader_program->release();
}

bool BreakingShaderProgram::addShader(QOpenGLShader *shader)
{
    m_opengl_shader_program->addShader(shader);
}

