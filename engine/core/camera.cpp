#include "component.h"
#include "gameobject.h"
#include "transform.h"
#include "camera.h"

Camera::Camera( GameObject* parent )
    : Component( parent ), m_upVector( 0.0f, 1.0f, 0.0f )
    , m_viewCenter( 0.0f, 0.0f, 0.0f )
    , m_cameraToCenter( 0.0f, 0.0f, -1.0f )
    , m_projectionType( Camera::OrthogonalProjection )
    , m_nearPlane( 0.1f )
    , m_farPlane( 1024.0f )
    , m_fieldOfView( 60.0f )
    , m_aspectRatio( 1.0f )
    , m_left( -0.5 )
    , m_right( 0.5f )
    , m_bottom( -0.5f )
    , m_top( 0.5f )
    , m_viewMatrixDirty( true )
    , m_viewProjectionMatrixDirty( true )
{
    updateOrthogonalProjection();
}
Camera* Camera::main = nullptr;


Camera::~Camera() {
}

Camera::ProjectionType Camera::projectionType() const
{
    return m_projectionType;
}

void Camera::setProjectionType(Camera::ProjectionType type)
{
    m_projectionType = type;
}

QVector3D Camera::viewCenter() const
{
    return m_viewCenter;
}

QVector3D Camera::viewVector() const
{
    return m_cameraToCenter;
}

QVector3D Camera::upVector() const
{
    return m_upVector;
}
