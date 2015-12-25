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

void Camera::rotate(const QQuaternion& q) {
    m_upVector = q.rotatedVector( m_upVector );
    m_cameraToCenter = q.rotatedVector( m_cameraToCenter );
    m_viewCenter = gameObject()->transform()->position + m_cameraToCenter;
}

void Camera::rotateAboutViewCenter( const QQuaternion& q )
{
    m_upVector = q.rotatedVector( m_upVector );
    m_cameraToCenter = q.rotatedVector( m_cameraToCenter );
    gameObject()->transform()->position = m_viewCenter - m_cameraToCenter;
}



void Camera::translate( const QVector3D& vLocal, CameraTranslationOption option )
{
    // Calculate the amount to move by in world coordinates
    QVector3D vWorld;
    if ( !qFuzzyIsNull( vLocal.x() ) )
    {
        // Calculate the vector for the local x axis
        QVector3D x = QVector3D::crossProduct( m_cameraToCenter,m_upVector ).normalized();
        vWorld += vLocal.x() * x;
    }

    if ( !qFuzzyIsNull( vLocal.y() ) )
        vWorld += vLocal.y() * m_upVector;

    if ( !qFuzzyIsNull( vLocal.z() ) )
        vWorld += vLocal.z() * m_cameraToCenter.normalized();

    // Update the camera position using the calculated world vector
    gameObject()->transform()->position += vWorld;

    // May be also update the view center coordinates
    if ( option == TranslateViewCenter )
        m_viewCenter += vWorld;

    // Refresh the camera -> view center vector
    m_cameraToCenter = m_viewCenter - gameObject()->transform()->position;

    // Calculate a new up vector. We do this by:
    // 1) Calculate a new local x-direction vector from the cross product of the new
    //    camera to view center vector and the old up vector.
    // 2) The local x vector is the normal to the plane in which the new up vector
    //    must lay. So we can take the cross product of this normal and the new
    //    x vector. The new normal vector forms the last part of the orthonormal basis
    QVector3D x = QVector3D::crossProduct( m_cameraToCenter, m_upVector ).normalized();
    m_upVector = QVector3D::crossProduct( x, m_cameraToCenter ).normalized();

    m_viewMatrixDirty = true;
}

void Camera::translateWorld(const QVector3D& vWorld , CameraTranslationOption option )
{
    // Update the camera position using the calculated world vector
    gameObject()->transform()->position += vWorld;

    // May be also update the view center coordinates
    if ( option == TranslateViewCenter )
        m_viewCenter += vWorld;

    // Refresh the camera -> view center vector
    m_cameraToCenter = m_viewCenter - gameObject()->transform()->position;

    m_viewMatrixDirty = true;
}

QQuaternion Camera::tiltRotation( const float& angle ) const
{
    QVector3D xBasis = QVector3D::crossProduct( m_upVector, m_cameraToCenter.normalized() ).normalized();
    return QQuaternion::fromAxisAndAngle( xBasis, -angle );
}

QQuaternion Camera::panRotation( const float& angle ) const
{
    return QQuaternion::fromAxisAndAngle(m_upVector, angle );
}

QQuaternion Camera::panRotation( const float& angle, const QVector3D& axis ) const
{
    return QQuaternion::fromAxisAndAngle( axis, angle );
}

QQuaternion Camera::rollRotation( const float& angle ) const
{
    return QQuaternion::fromAxisAndAngle(m_cameraToCenter, -angle );
}

void Camera::tilt( const float& angle )
{
    QQuaternion q = tiltRotation( angle );
    rotate( q );
}

void Camera::pan( const float& angle )
{
    QQuaternion q = panRotation( -angle );
    rotate( q );
}

void Camera::pan( const float& angle, const QVector3D& axis )
{
    QQuaternion q = panRotation( -angle, axis );
    rotate( q );
}

void Camera::roll( const float& angle )
{
    QQuaternion q = rollRotation( -angle );
    rotate( q );
}

void Camera::tiltAboutViewCenter( const float& angle )
{
    QQuaternion q = tiltRotation( -angle );
    rotateAboutViewCenter( q );
}

void Camera::panAboutViewCenter( const float& angle )
{
    QQuaternion q = panRotation( angle );
    rotateAboutViewCenter( q );
}

void Camera::rollAboutViewCenter( const float& angle )
{
    QQuaternion q = rollRotation( angle );
    rotateAboutViewCenter( q );
}

