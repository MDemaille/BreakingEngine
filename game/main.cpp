#include "engine/rendering/breakingwindow.h"
#include "engine/core/scene.h"
#include "engine/rendering/renderer.h"
#include "engine/core/gameobject.h"
#include "engine/core/transform.h"
#include "engine/core/updatable.h"

#include "engine/core/camera.h"
#include <QApplication>
#include "scene1.h"


int main(int argc, char *argv[])
{
    //QTApplication
    QApplication a(argc, argv);
    //Surface
    QSurfaceFormat format;
    format.setSamples(16);
    format.setMajorVersion(2);
    format.setMinorVersion(0);
    format.setDepthBufferSize(24);
    format.setProfile(QSurfaceFormat::CoreProfile);

    //BreakingWindow
    BreakingWindow w;
    w.setFormat(format);
    w.setSurfaceType(QWindow::SurfaceType::OpenGLSurface);
    w.resize(640, 480);

    // Create Scene
    Scene* scene = new Scene1();
    w.setupScene(scene);
    w.show();

    return a.exec();
}
