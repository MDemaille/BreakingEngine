TEMPLATE = app
QT += core gui network
TARGET = BreakinEngine
CONFIG += c++11
LIBS+=
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#Engine content
include(engine/BreakingEngine-engine.pri)
#Game content
include(game/BreakingEngine-game.pri)

SUBDIRS += engine game

RESOURCES += \
    engine.qrc

DISTFILES += \
    qtbreaking.vert
