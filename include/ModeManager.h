#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include <QObject>

class SceneObject;

/**
 * @brief Manages the current interaction mode (Object Mode vs Edit Mode)
 *
 * ModeManager controls whether the user is manipulating whole objects
 * or editing individual mesh elements (vertices, edges, faces).
 */
class ModeManager : public QObject
{
    Q_OBJECT

public:
    enum Mode {
        ObjectMode,  // Manipulate whole objects (move, rotate, scale, delete)
        EditMode     // Edit mesh elements (vertices, edges, faces)
    };
    Q_ENUM(Mode)

    explicit ModeManager(QObject *parent = nullptr);
    ~ModeManager();

    // Mode management
    Mode currentMode() const { return m_mode; }
    void setMode(Mode mode);

    // Active object (the object being edited in Edit Mode)
    SceneObject* activeObject() const { return m_activeObject; }
    void setActiveObject(SceneObject* object);

    // Convenience methods
    bool isObjectMode() const { return m_mode == ObjectMode; }
    bool isEditMode() const { return m_mode == EditMode; }

signals:
    void modeChanged(Mode mode);
    void activeObjectChanged(SceneObject* object);

private:
    Mode m_mode;
    SceneObject* m_activeObject;
};

#endif // MODEMANAGER_H
