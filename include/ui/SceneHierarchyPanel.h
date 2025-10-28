#ifndef SCENEHIERARCHYPANEL_H
#define SCENEHIERARCHYPANEL_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

class ObjectManager;
class SelectionManager;
class Collection;
class SceneObject;

/**
 * @brief Custom delegate for rendering visibility eye icon in tree view
 */
class VisibilityDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit VisibilityDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override;

    bool editorEvent(QEvent* event, QAbstractItemModel* model,
                    const QStyleOptionViewItem& option,
                    const QModelIndex& index) override;

    QSize sizeHint(const QStyleOptionViewItem& option,
                   const QModelIndex& index) const override;

signals:
    void visibilityToggled(const QModelIndex& index);
};

/**
 * @brief Custom model for drag & drop support with UUID-based serialization
 */
class SceneHierarchyModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit SceneHierarchyModel(QObject* parent = nullptr);

    // Override drag & drop methods to use UUIDs instead of serializing void*
    QStringList mimeTypes() const override;
    QMimeData* mimeData(const QModelIndexList& indexes) const override;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action,
                     int row, int column, const QModelIndex& parent) override;
    Qt::DropActions supportedDropActions() const override;

signals:
    void itemDropped(const QString& itemUuid, const QString& targetCollectionUuid, int itemType);
};

/**
 * @brief Scene Hierarchy Panel - Blender-style outliner for objects and collections
 */
class SceneHierarchyPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SceneHierarchyPanel(ObjectManager* objectManager,
                                 SelectionManager* selectionManager,
                                 QWidget* parent = nullptr);
    ~SceneHierarchyPanel();

    // Collection management
    Collection* sceneCollection() const { return m_sceneCollection; }
    Collection* createCollection(const QString& name, Collection* parent = nullptr);
    void deleteCollection(Collection* collection);

    // Tree refresh
    void rebuildTree();

signals:
    void objectSelected(SceneObject* object);
    void collectionCreated(Collection* collection);
    void collectionDeleted(Collection* collection);

private slots:
    void onItemClicked(const QModelIndex& index);
    void onItemDoubleClicked(const QModelIndex& index);
    void onCustomContextMenu(const QPoint& pos);
    void onVisibilityToggled(const QModelIndex& index);
    void onItemDropped(const QString& itemUuid, const QString& targetCollectionUuid, int itemType);

    // ObjectManager signals
    void onObjectAdded(SceneObject* object);
    void onObjectRemoved(SceneObject* object);

private:
    void setupUI();
    void setupConnections();
    void createContextMenu(const QPoint& pos);

    // Tree building
    void addCollectionToTree(Collection* collection, QStandardItem* parentItem);
    void addObjectToTree(SceneObject* object, QStandardItem* parentItem);

    QStandardItem* findItemByObject(SceneObject* object);
    QStandardItem* findItemByCollection(Collection* collection);

    // UUID lookup helpers
    Collection* findCollectionByUuid(const QString& uuidStr, Collection* root = nullptr);
    SceneObject* findObjectByUuid(const QString& uuidStr);
    void removeObjectFromAllCollections(SceneObject* object, Collection* root);
    bool isDescendantOf(Collection* potential, Collection* ancestor);

    // UI components
    QTreeView* m_treeView;
    SceneHierarchyModel* m_model;
    VisibilityDelegate* m_visibilityDelegate;

    // Data
    ObjectManager* m_objectManager;
    SelectionManager* m_selectionManager;
    Collection* m_sceneCollection;  // Root collection
};

#endif // SCENEHIERARCHYPANEL_H
