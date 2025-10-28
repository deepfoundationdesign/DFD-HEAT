#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QUuid>

class SceneObject;
namespace Qt3DCore {
    class QEntity;
}

/**
 * @brief Manages the lifecycle of scene objects
 *
 * ObjectManager handles creation, deletion, and duplication of objects.
 * All objects are parented to a root entity for scene graph management.
 */
class ObjectManager : public QObject
{
    Q_OBJECT

public:
    explicit ObjectManager(Qt3DCore::QEntity* rootEntity, QObject *parent = nullptr);
    ~ObjectManager();

    // Object lifecycle
    void addObject(SceneObject* object);
    void removeObject(SceneObject* object);
    SceneObject* duplicateObject(SceneObject* object);

    // Object creation (primitives)
    SceneObject* createBox(const QVector3D& dimensions = QVector3D(1, 1, 1));
    SceneObject* createCylinder(float radius = 0.5f, float height = 2.0f);
    SceneObject* createSphere(float radius = 1.0f);

    // Object access
    QVector<SceneObject*> allObjects() const { return m_objects; }
    SceneObject* findByUuid(const QUuid& uuid) const;
    int objectCount() const { return m_objects.size(); }

    // Root entity (for scene graph)
    Qt3DCore::QEntity* rootEntity() const { return m_rootEntity; }

signals:
    void objectAdded(SceneObject* obj);
    void objectRemoved(SceneObject* obj);

private:
    Qt3DCore::QEntity* m_rootEntity;
    QVector<SceneObject*> m_objects;
};

#endif // OBJECTMANAGER_H
