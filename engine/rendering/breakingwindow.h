#ifndef BREAKINGRENDER_H
#define BREAKINGRENDER_H

#include "openglwindow.h"

#include "engine/core/common.h"
#include <QTimer>

class BreakingWindow : public virtual OpenGLWindow
{
    Q_OBJECT
private:
    Scene* m_scene = nullptr;
    QTimer* m_timer;
public:
    explicit BreakingWindow(QWindow* parent=0);
    virtual~BreakingWindow();

    virtual void setupScene(Scene* scene);

    virtual void initialize();
    virtual void render();

};

#endif // BREAKINGRENDER_H
