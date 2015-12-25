#include "scene.h"
#include "component.h"
#include "gameobject.h"
#include "engine/rendering/renderer.h"
#include "engine/core/updatable.h"
#include <GL/gl.h>
#include "camera.h"
#include "engine/core/time.h"
#include "engine/rendering/breakingwindow.h"

Scene::Scene(BreakingWindow* parent):QObject(parent)
{

}

Scene::~Scene() {
    while(!m_gameObjects.empty()) {
        GameObject* go = m_gameObjects.front();
        m_gameObjects.pop_front();
        delete go;
    }
}

void Scene::init() {

}


void Scene::update() {
    for(GameObject* gameObject: m_gameObjects) {
        QList<Updatable*> updatables;

        gameObject->getComponents<Updatable>(&updatables);

        for(Updatable* updatable: updatables) {
            updatable->update();
        }
    }
}

BreakingWindow* Scene::parent() {
    BreakingWindow* ptr = dynamic_cast<BreakingWindow*>(QObject::parent());
    return ptr;
}

void Scene::render() {
    Time::singleton.newFrame();
    glViewport(0, 0, this->parent()->width(), this->parent()->height());

    glClearColor(0.0, 0.0, 0.0, 0.0);
    //Clean flags
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Projection Mode
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    qDebug()<<"Scene::render():projection";


    //If a main Camera is used
//    if(Camera::main != nullptr) {
        //We load it
//        Camera* current = Camera::main;
//        QMatrix4x4 projection = current->projectionMatrix();
//        QMatrix4x4 view = current->viewMatrix();

        //We chose in function of the mode the better solution
//        if(current->projectionType() == Camera::PerspectiveProjection) {
            //Perspective by glut
//            gluPerspective(current->fieldOfView(),current->aspectRatio(),
//                           current->nearPlane(),current->farPlane());
            //replace by glFrustum(...)
//            glFrustum(current->left(),current->right(),current->bottom(),
//                      current->top(),current->nearPlane(),current->farPlane());
//            glFrustum(-current->right(),
//                      current->aspectRatio()*current->right(),
//                      -current->top(),
//                      current->nearPlane()* ((M_PI/180)*current->fieldOfView()/2),
//                      current->nearPlane(),
//                      current->farPlane());
//        }
//        else {
            //Orthogonal camera
//            glOrtho(current->left(),current->right(),
//                    current->bottom(),current->top(),
//                    current->nearPlane(),current->farPlane());
//        }

//    }
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    if(Camera::main != nullptr) {

//        if(Camera::main->projectionType() == Camera::PerspectiveProjection) {

//            Camera::main->look();
//        }

//    }


    // Camera::main->m_viewMatrixDirty = true;

    for(GameObject* gameObject: m_gameObjects) {
        QList<Renderer*> renderers = gameObject->getComponents<Renderer>();
        for(Renderer* renderer: renderers) {
            renderer->render();
        }
    }
}

void Scene::addGameObject(GameObject *gameObject)
{
    m_gameObjects.append(gameObject);
}

void Scene::removeGameObject(GameObject *gameObject)
{
    m_gameObjects.removeOne(gameObject);
}
