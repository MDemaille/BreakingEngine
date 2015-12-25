#ifndef BSPMANAGER_H
#define BSPMANAGER_H


#include <QtCore>
#include <engine/opengl/breakingshaderprogram.h>

/**
 * @brief The BSPManager classe est un manager contenant l'ensemble des programmes Shaders de
 * l'application pour accélérer la recherche de ces derniers.
 */
class BSPManager
{
protected:
    QMap<QString,BreakingShaderProgram*> m_shaders;
    static QString defaultShaderName;
public:
    BSPManager();
    virtual ~BSPManager();

    static BSPManager* Instance() {
        static BSPManager singleton;
        return &singleton;
    }

    bool haveBSPWithName(QString name) {
        return m_shaders.contains(name);
    }

    bool addBreakingShaderProgram(QString name, BreakingShaderProgram* bsp) {
        if(haveBSPWithName(name))
            return false;

        m_shaders[name] = bsp;
        bsp->start();
    }

    BreakingShaderProgram* getBSPByName(QString name) {
        return m_shaders[name];
    }

    BreakingShaderProgram* getDefaultBreakingShaderProgram() {
        return m_shaders[BSPManager::defaultShaderName];
    }


};


#endif // BSPMANAGER_H
