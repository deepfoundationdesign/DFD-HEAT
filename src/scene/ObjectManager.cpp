#include "scene/ObjectManager.h"
#include "scene/SceneObject.h"
#include "scene/BoxObject.h"
#include <QDebug>

ObjectManager::ObjectManager(Qt3DCore::QEntity* rootEntity, QObject *parent)
    : QObject(parent)
    , m_rootEntity(rootEntity)
{
    qDebug() << "ObjectManager created";
}

ObjectManager::~ObjectManager()
{
    // Clean up all objects
    qDeleteAll(m_objects);
    m_objects.clear();
}

void ObjectManager::addObject(SceneObject* object)
{
    if (!object) {
        qWarning() << "Cannot add null object";
        return;
    }

    if (m_objects.contains(object)) {
        qWarning() << "Object already managed:" << object->name();
        return;
    }

    m_objects.append(object);
    qDebug() << "Object added:" << object->name() << "Total objects:" << m_objects.size();
    emit objectAdded(object);
}

void ObjectManager::removeObject(SceneObject* object)
{
    if (!object) {
        qWarning() << "Cannot remove null object";
        return;
    }

    int index = m_objects.indexOf(object);
    if (index == -1) {
        qWarning() << "Object not managed:" << object->name();
        return;
    }

    m_objects.removeAt(index);
    qDebug() << "Object removed:" << object->name() << "Total objects:" << m_objects.size();
    emit objectRemoved(object);

    // Delete the object
    object->deleteLater();
}

SceneObject* ObjectManager::duplicateObject(SceneObject* object)
{
    if (!object) {
        qWarning() << "Cannot duplicate null object";
        return nullptr;
    }

    // TODO: Implement duplication for each object type
    // For now, just create a new box if it's a box
    BoxObject* boxObj = qobject_cast<BoxObject*>(object);
    if (boxObj) {
        SceneObject* duplicate = createBox(boxObj->dimensions());
        duplicate->setLocation(boxObj->location() + QVector3D(1, 0, 0));  // Offset slightly
        duplicate->setRotation(boxObj->rotation());
        duplicate->setScale(boxObj->scale());
        duplicate->setName(boxObj->name() + "_copy");
        return duplicate;
    }

    qWarning() << "Duplication not implemented for this object type";
    return nullptr;
}

SceneObject* ObjectManager::createBox(const QVector3D& dimensions)
{
    auto* box = new BoxObject(dimensions.x(), dimensions.y(), dimensions.z(), m_rootEntity);
    addObject(box);
    return box;
}

SceneObject* ObjectManager::createCylinder(float radius, float height)
{
    // TODO: Implement CylinderObject
    qWarning() << "CylinderObject not yet implemented";
    return nullptr;
}

SceneObject* ObjectManager::createSphere(float radius)
{
    // TODO: Implement SphereObject
    qWarning() << "SphereObject not yet implemented";
    return nullptr;
}

SceneObject* ObjectManager::findByUuid(const QUuid& uuid) const
{
    for (SceneObject* obj : m_objects) {
        if (obj->uuid() == uuid) {
            return obj;
        }
    }
    return nullptr;
}
