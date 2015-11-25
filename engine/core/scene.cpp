#include "scene.h"
#include "component.h"
#include "gameobject.h"
#include "engine/rendering/renderer.h"
#include "engine/core/updatable.h"
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "camera.h"

Scene::Scene(QObject* parent):QObject(parent)
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

void Scene::render() {
    //Clean flags
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Projection Mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //If a main Camera is used
    if(Camera::main != nullptr) {
        //We load it
        Camera* current = Camera::main;
        //We chose in function of the mode the better solution
        if(current->projectionType() == Camera::PerspectiveProjection) {
            //Perspective by glut
            gluPerspective(current->fieldOfView(),current->aspectRatio(),
                           current->nearPlane(),current->farPlane());
            //replace glFrustum(...)
        }
        else {
            //Orthogonal camera
            glOrtho(current->left(),current->right(),
                    current->bottom(),current->top(),
                    current->nearPlane(),current->farPlane());
        }

    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(Camera::main != nullptr) {
        QVector3D pos = Camera::main->gameObject()->transform()->position;
        QVector3D view = Camera::main->viewCenter();
        QVector3D up = Camera::main->upVector();
        if(Camera::main->projectionType() == Camera::PerspectiveProjection)
            gluLookAt(pos.x(),pos.y(),pos.z(),
                      view.x(),view.y(),view.z(),
                      up.x(),up.y(),up.z()
                      );

    }



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
