#include "scene1.h"
#include "engine/rendering/breakingwindow.h"
#include "engine/core/scene.h"
#include "engine/rendering/renderer.h"
#include "engine/core/gameobject.h"
#include "engine/core/transform.h"
#include "engine/core/updatable.h"
 #include <QQuaternion>
#include "engine/core/time.h"
#include "engine/core/camera.h"

class CubeRenderer : public virtual Renderer {

    GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
      {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
    GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
      {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
      {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
    GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */
public:
    void init() {
        setObjectName("rendering/CubeRenderer");
        /* Setup cube vertex data. */
         v[0][0] = v[1][0] = v[2][0] = v[3][0] = -.5;
         v[4][0] = v[5][0] = v[6][0] = v[7][0] = .5;
         v[0][1] = v[1][1] = v[4][1] = v[5][1] = -.5;
         v[2][1] = v[3][1] = v[6][1] = v[7][1] = .5;
         v[0][2] = v[3][2] = v[4][2] = v[7][2] = .5;
         v[1][2] = v[2][2] = v[5][2] = v[6][2] = -.5;
    }

    virtual void renderContent() {
    //    m_textures[0]->bind();
        glTranslatef(gameObject()->transform()->position.x(),
                     gameObject()->transform()->position.y(),
                     gameObject()->transform()->position.z());
        glRotatef(gameObject()->transform()->rotation.x(),
                  1,0,0);
        glRotatef(gameObject()->transform()->rotation.y(),
                  0,1,0);
        glRotatef(gameObject()->transform()->rotation.z(),
                  0,0,1);
        glScalef(gameObject()->transform()->scaling.x(),
                 gameObject()->transform()->scaling.y(),
                 gameObject()->transform()->scaling.z());

        int i;

        for (i = 0; i < 6; i++) {
            glBegin(GL_QUADS);
            glNormal3fv(&n[i][0]);
            glVertex3fv(&v[faces[i][0]][0]);
            glVertex3fv(&v[faces[i][1]][0]);
            glVertex3fv(&v[faces[i][2]][0]);
            glVertex3fv(&v[faces[i][3]][0]);
            glEnd();
        }
//        static GLUquadricObj *quadric = gluNewQuadric();

//        gluQuadricDrawStyle(quadric, GLU_FILL );
//        gluSphere( quadric , 1 , 36 , 18 );

    }
};


class Triangle : public virtual Renderer {
private:


    virtual void renderContent() {
        glColor3f(1.0f,1.0f,1.0f);
        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0.707f,0);
            glVertex3f(-0.5f,-0.5f,0);
            glVertex3f(0.5f,-0.5f,0);
        }
        glEnd();
    }
};

class LandMark : public virtual Renderer {

    virtual void renderContent() {
        glColor3f(1.0f,0.0f,0.0f);
        glBegin(GL_LINES);
        {
            glVertex3f(0,0,0);
            glVertex3f(0.5,0,0);
        }
        glEnd();
        glColor3f(0.0f,1.0f,0.0f);
        glBegin(GL_LINES);
        {
            glVertex3f(0,0,0);
            glVertex3f(0,0.5,0);
        }

        glColor3f(0.0f,0.0f,1.0f);
        glBegin(GL_LINES);
        {
            glVertex3f(0,0,0);
            glVertex3f(0,0,0.5);
        }
        glColor3f(1.0f,1.0f,1.0f);
    }
};

///Script Example
class AnimatorScript : public virtual Updatable {

    float PI = 3.14;
    float t;
    virtual void update() {
        if(t==1) {
            t=0;
            Camera::main->translateWorld(QVector3D(-0.0f,0.0f,-3.f)*Time::deltaTime(),Camera::CameraTranslationOption::TranslateViewCenter);

        }

        //Camera::main->tiltAboutViewCenter(1);
        //Camera::main->translate(QVector3D(-0.0f,0.0f,-.3f),Camera::CameraTranslationOption::TranslateViewCenter);
        qDebug() << "Time:delta:"<<Time::deltaTime();

        Camera::main->pan(1 * Time::deltaTime());
        //Camera::main->gameObject()->transform()->position+= QVector3D(-1.0f,0,0);
        //Camera::main->setViewCenter(Camera::main->viewCenter()+QVector3D(-1.0f,0,0));
       t+=Time::deltaTime();
    }

};
Scene1::Scene1()
{
    //Camera GameObject
    GameObject* camera = new GameObject("_Camera");
    camera->transform()->position.setZ(3.0f);
    camera->transform()->position.setX(9.0f);
    //Camera Component
    Camera* cameraComponent = new Camera();

    //Main Camera
    Camera::main = cameraComponent;
    cameraComponent->setAspectRatio(4.0/3.0f);
    cameraComponent->setProjectionType(Camera::PerspectiveProjection);
    //Add Camera Component
    camera->addComponent(cameraComponent);

    //Script example
    AnimatorScript* animator = new AnimatorScript();
    camera->addComponent(animator);
    //Add GameObject in the scene
    this->addGameObject(camera);

    //LandMark GameObject
    GameObject* landMark = new GameObject("_LandMark");
//    LandMark:Renderer component
    LandMark* lm = new LandMark();
    landMark->addComponent(lm);
    this->addGameObject(landMark);

//    Cube GameObject
    GameObject* cube = new GameObject("Cube");
    CubeRenderer* renderer = new CubeRenderer();
    renderer->init();
    cube->addComponent(renderer);
    this->addGameObject(cube);


}

