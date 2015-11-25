#ifndef CAMERA_H
#define CAMERA_H
#include "engine/core/common.h"
#include "engine/core/component.h"
#include "engine/core/transform.h"
#include <QVector3D>
#include <QMatrix4x4>

class Camera : public virtual Component
{
    Q_OBJECT
public:
    enum ProjectionType
    {
        OrthogonalProjection,
        PerspectiveProjection
    };

    enum CameraTranslationOption
    {
        TranslateViewCenter,
        DontTranslateViewCenter
    };
private:
    QVector3D m_upVector;
    QVector3D m_viewCenter;
    mutable QMatrix4x4 m_viewMatrix;
    mutable QMatrix4x4 m_projectionMatrix;
    mutable QMatrix4x4 m_viewProjectionMatrix;

    QVector3D m_cameraToCenter; // The vector from the camera position to the view center

    Camera::ProjectionType m_projectionType;

    float m_nearPlane;
    float m_farPlane;

    float m_fieldOfView;
    float m_aspectRatio;

    float m_left;
    float m_right;
    float m_bottom;
    float m_top;
    mutable bool m_viewMatrixDirty = true;
    mutable bool m_viewProjectionMatrixDirty = true;
public:


    static Camera* main;
    explicit Camera(GameObject* parent=0);
    virtual ~Camera();



    QVector3D upVector() const;
    QVector3D viewCenter() const;
    QVector3D viewVector() const;

    Camera::ProjectionType projectionType() const;
    void setProjectionType(Camera::ProjectionType type);

    inline void updatePerpectiveProjection()
    {
        m_projectionMatrix.setToIdentity();
        m_projectionMatrix.perspective( m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane );
        m_viewProjectionMatrixDirty = true;
    }

    inline void updateOrthogonalProjection()
    {
        m_projectionMatrix.setToIdentity();
        m_projectionMatrix.ortho( m_left, m_right, m_bottom, m_top, m_nearPlane, m_farPlane );
        m_viewProjectionMatrixDirty = true;
    }

    void setOrthographicProjection( float left, float right,
                                    float bottom, float top,
                                    float nearPlane, float farPlane ) {
        setLeft(left);
        setRight(right);
        setBottom(bottom);
        setTop(top);
        setNearPlane(nearPlane);
        setFarPlane(farPlane);
        updateOrthogonalProjection();
    }

    void setPerspectiveProjection( float fieldOfView, float aspect,
                                   float nearPlane, float farPlane ) {

        setFieldOfView(fieldOfView);
        setAspectRatio(aspect);
        setNearPlane(nearPlane);
        setFarPlane(farPlane);
        updatePerpectiveProjection();
    }

    void setNearPlane( const float& nearPlane ) {
        m_nearPlane = nearPlane;
    }

    float nearPlane() const {
        return m_nearPlane;
    }

    void setFarPlane( const float& nearPlane ) {
        m_farPlane = nearPlane;
    }

    float farPlane() const {
        return m_farPlane;
    }

    void setFieldOfView( const float& fieldOfView ) {
        m_fieldOfView = fieldOfView;
    }

    void setViewCenter(QVector3D v) {
        m_viewCenter = v;
    }


    float fieldOfView() const {
        return m_fieldOfView;
    }

    void setAspectRatio( const float& aspectRatio ) {
        m_aspectRatio = aspectRatio;
    }

    float aspectRatio() const {
       return m_aspectRatio;
    }

    void setLeft( const float& left ) {
        m_left =left;
    }

    float left() const {
        return m_left;
    }

    void setRight( const float& right ) {
        m_right = right;
    }

    float right() const {
        return m_right;
    }

    void setBottom( const float& bottom ) {
        m_bottom = bottom;
    }

    float bottom() const {
        return m_bottom;
    }

    void setTop( const float& top ){
        m_top = top;
    }

    float top() const {
        return m_top;
    }



    QMatrix4x4 viewMatrix() {
        if (m_viewMatrixDirty)
        {
            m_viewMatrix.setToIdentity();
            m_viewMatrix.lookAt( gameObject()->transform()->position, m_viewCenter, m_upVector );
            m_viewMatrixDirty = false;
        }
        return m_viewMatrix;
    }

    QMatrix4x4 projectionMatrix() const {
        return m_projectionMatrix;
    }
    QMatrix4x4 viewProjectionMatrix() {
        if ( m_viewMatrixDirty || m_viewProjectionMatrixDirty )
        {
            m_viewProjectionMatrix = m_projectionMatrix * viewMatrix();
            m_viewProjectionMatrixDirty = false;
        }
        return m_viewProjectionMatrix;
    }



//    QQuaternion tiltRotation( const float& angle ) const;
//    QQuaternion panRotation( const float& angle ) const;
//    QQuaternion panRotation( const float& angle, const QVector3D& axis ) const;
//    QQuaternion rollRotation( const float& angle ) const;



};

#endif // CAMERA_H
