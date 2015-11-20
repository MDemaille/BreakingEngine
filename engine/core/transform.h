#ifndef CORE_TRANSFORM_H
#define CORE_TRANSFORM_H

#include "engine/core/common.h"
#include "engine/core/component.h"
#include "engine/core/gameobject.h"

#include <QString>
#include <QObject>

class Transform : public virtual Component {
public:
    //static const QString NAME;
    explicit Transform(GameObject* parent=0);
    virtual ~Transform();
};

#endif // TRANSFORM_H
