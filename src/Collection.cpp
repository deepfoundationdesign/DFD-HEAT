#include "Collection.h"
#include "SceneObject.h"
#include <QDebug>

Collection::Collection(const QString& name, QObject* parent)
    : QObject(parent)
    , m_name(name)
    , m_uuid(QUuid::createUuid())
    , m_visible(true)
    , m_parentCollection(nullptr)
{
}

Collection::~Collection()
{
    // Clean up child collections
    qDeleteAll(m_childCollections);
    m_childCollections.clear();
}

void Collection::setName(const QString& name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged(name);
    }
}

void Collection::setVisible(bool visible)
{
    if (m_visible != visible) {
        m_visible = visible;
        emit visibilityChanged(visible);

        // Apply visibility to all objects in this collection
        for (SceneObject* obj : m_objects) {
            if (obj) {
                obj->setVisible(visible);
            }
        }

        // Recursively apply to child collections
        for (Collection* child : m_childCollections) {
            if (child) {
                child->setVisible(visible);
            }
        }
    }
}

void Collection::addObject(SceneObject* object)
{
    if (!object || m_objects.contains(object)) {
        return;
    }

    m_objects.append(object);

    // Apply collection visibility to object
    if (!m_visible) {
        object->setVisible(false);
    }

    emit objectAdded(object);
}

void Collection::removeObject(SceneObject* object)
{
    if (m_objects.removeOne(object)) {
        emit objectRemoved(object);
    }
}

bool Collection::containsObject(SceneObject* object) const
{
    return m_objects.contains(object);
}

void Collection::addChildCollection(Collection* collection)
{
    if (!collection || m_childCollections.contains(collection)) {
        return;
    }

    m_childCollections.append(collection);
    collection->setParentCollection(this);

    // Apply visibility to child
    if (!m_visible) {
        collection->setVisible(false);
    }

    emit childCollectionAdded(collection);
}

void Collection::removeChildCollection(Collection* collection)
{
    if (m_childCollections.removeOne(collection)) {
        collection->setParentCollection(nullptr);
        emit childCollectionRemoved(collection);
    }
}

void Collection::setParentCollection(Collection* parent)
{
    m_parentCollection = parent;
}
