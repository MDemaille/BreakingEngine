#ifndef CORE_TRANSFORM_H
#define CORE_TRANSFORM_H

#include "engine/core/common.h"
#include "engine/core/component.h"
#include "engine/core/gameobject.h"

#include <QString>
#include <QVector3D>
#include <QQuaternion>
#include <QObject>

class Transform : public virtual Component {
    Q_OBJECT
public:
    //static const QString NAME;
    explicit Transform(GameObject* parent=0);
    virtual ~Transform();

    QVector3D position;
    QVector3D scaling;
    QQuaternion rotation;
};

#endif // TRANSFORM_H
