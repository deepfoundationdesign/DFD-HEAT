#include "ModeManager.h"
#include <QDebug>

ModeManager::ModeManager(QObject *parent)
    : QObject(parent)
    , m_mode(ObjectMode)
    , m_activeObject(nullptr)
{
    qDebug() << "ModeManager created - starting in Object Mode";
}

ModeManager::~ModeManager()
{
}

void ModeManager::setMode(Mode mode)
{
    if (m_mode == mode)
        return;

    // Cannot enter Edit Mode without an active object
    if (mode == EditMode && !m_activeObject) {
        qWarning() << "Cannot enter Edit Mode: No active object selected";
        return;
    }

    qDebug() << "Mode changed:" << (mode == ObjectMode ? "Object Mode" : "Edit Mode");
    m_mode = mode;
    emit modeChanged(m_mode);
}

void ModeManager::setActiveObject(SceneObject* object)
{
    if (m_activeObject == object)
        return;

    m_activeObject = object;
    qDebug() << "Active object changed:" << (object ? "Object selected" : "No selection");
    emit activeObjectChanged(m_activeObject);

    // If we're in Edit Mode but lost the active object, return to Object Mode
    if (m_mode == EditMode && !m_activeObject) {
        setMode(ObjectMode);
    }
}
