#include "breakingwindow.h"
#include "engine/core/scene.h"
#include <QDebug>

BreakingWindow::BreakingWindow(QWindow* parent) : OpenGLWindow(parent)
{
    setTitle("BreakingEngine");
}

BreakingWindow::~BreakingWindow()
{
    if(m_scene!= nullptr)
        delete m_scene;

    delete m_timer;
}

void BreakingWindow::setupScene(Scene *scene)
{
    if(m_scene != nullptr)
        delete m_scene;
    m_scene = scene;
}

void BreakingWindow::initialize() {
    m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(renderNow()));
    m_scene->init();
    m_timer->start(1000.0/60.0);
}


void BreakingWindow::render()
{
    qDebug() << "Scene::update()";
   m_scene->update();
   qDebug() << "Scene::render()";
   m_scene->render();
}
