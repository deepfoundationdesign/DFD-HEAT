#ifndef COLLECTION_H
#define COLLECTION_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QUuid>

class SceneObject;

/**
 * @brief Collection class for grouping scene objects (like Blender collections)
 *
 * Collections can contain objects and other collections (hierarchical).
 * Each collection has visibility control that affects all contained objects.
 */
class Collection : public QObject
{
    Q_OBJECT

public:
    explicit Collection(const QString& name = "Collection", QObject* parent = nullptr);
    ~Collection();

    // Basic properties
    QString name() const { return m_name; }
    void setName(const QString& name);

    QUuid uuid() const { return m_uuid; }

    // Visibility
    bool isVisible() const { return m_visible; }
    void setVisible(bool visible);

    // Object management
    void addObject(SceneObject* object);
    void removeObject(SceneObject* object);
    bool containsObject(SceneObject* object) const;
    QVector<SceneObject*> objects() const { return m_objects; }

    // Child collection management
    void addChildCollection(Collection* collection);
    void removeChildCollection(Collection* collection);
    QVector<Collection*> childCollections() const { return m_childCollections; }

    Collection* parentCollection() const { return m_parentCollection; }
    void setParentCollection(Collection* parent);

signals:
    void nameChanged(const QString& name);
    void visibilityChanged(bool visible);
    void objectAdded(SceneObject* object);
    void objectRemoved(SceneObject* object);
    void childCollectionAdded(Collection* collection);
    void childCollectionRemoved(Collection* collection);

private:
    QString m_name;
    QUuid m_uuid;
    bool m_visible;

    QVector<SceneObject*> m_objects;
    QVector<Collection*> m_childCollections;
    Collection* m_parentCollection;
};

#endif // COLLECTION_H
