#ifndef CORE_GAMEOBJECT_H
#define CORE_GAMEOBJECT_H

#include <QtCore>
#include <QObject>
#include "engine/core/common.h"

class GameObject : public virtual QObject {
  Q_OBJECT
public:
  explicit GameObject(GameObject* parent=0);
  GameObject(QString name,GameObject* parent=0);
  virtual ~GameObject();
public slots:

signals:

};

#endif
