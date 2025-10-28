#include "ui/SceneHierarchyPanel.h"
#include "scene/ObjectManager.h"
#include "scene/SelectionManager.h"
#include "scene/Collection.h"
#include "scene/SceneObject.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QMimeData>
#include <QDataStream>
#include <QDebug>

// Custom item roles for storing pointers
constexpr int ObjectRole = Qt::UserRole + 1;
constexpr int CollectionRole = Qt::UserRole + 2;
constexpr int VisibilityRole = Qt::UserRole + 3;
constexpr int ItemTypeRole = Qt::UserRole + 4;
constexpr int UuidRole = Qt::UserRole + 5;  // Store UUID as QString

enum ItemType {
    ObjectItem,
    CollectionItem
};

// Custom MIME type for drag & drop
constexpr const char* SCENE_HIERARCHY_MIME = "application/x-dfd-scene-hierarchy";

//==============================================================================
// SceneHierarchyModel Implementation
//==============================================================================

SceneHierarchyModel::SceneHierarchyModel(QObject* parent)
    : QStandardItemModel(parent)
{
}

QStringList SceneHierarchyModel::mimeTypes() const
{
    return QStringList() << SCENE_HIERARCHY_MIME;
}

QMimeData* SceneHierarchyModel::mimeData(const QModelIndexList& indexes) const
{
    if (indexes.isEmpty()) {
        return nullptr;
    }

    QMimeData* mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    // Only encode the first index (we only support single selection)
    QModelIndex index = indexes.first();
    if (index.column() != 0) {
        index = index.sibling(index.row(), 0);
    }

    QStandardItem* item = itemFromIndex(index);
    if (!item) {
        return mimeData;
    }

    // Store item type and UUID
    ItemType type = static_cast<ItemType>(item->data(ItemTypeRole).toInt());
    QString uuid = item->data(UuidRole).toString();

    stream << static_cast<int>(type);
    stream << uuid;

    // Store parent path (for reconstructing tree position)
    QStringList parentPath;
    QModelIndex parentIndex = index.parent();
    while (parentIndex.isValid()) {
        QStandardItem* parentItem = itemFromIndex(parentIndex);
        if (parentItem) {
            parentPath.prepend(parentItem->data(UuidRole).toString());
        }
        parentIndex = parentIndex.parent();
    }
    stream << parentPath;

    mimeData->setData(SCENE_HIERARCHY_MIME, encodedData);
    return mimeData;
}

bool SceneHierarchyModel::dropMimeData(const QMimeData* data, Qt::DropAction action,
                                       int row, int column, const QModelIndex& parent)
{
    if (!data || !data->hasFormat(SCENE_HIERARCHY_MIME)) {
        return false;
    }

    if (action == Qt::IgnoreAction) {
        return true;
    }

    // Decode the dragged item info
    QByteArray encodedData = data->data(SCENE_HIERARCHY_MIME);
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    int typeInt;
    QString uuid;
    QStringList parentPath;

    stream >> typeInt;
    stream >> uuid;
    stream >> parentPath;

    ItemType type = static_cast<ItemType>(typeInt);

    // Must drop onto a collection (not root)
    if (!parent.isValid()) {
        qDebug() << "[SceneHierarchyModel] Rejecting drop to root level";
        return false;
    }

    // Get target collection UUID from parent item
    QStandardItem* parentItem = itemFromIndex(parent);
    if (!parentItem) {
        return false;
    }

    // Only allow drops onto collections
    ItemType parentType = static_cast<ItemType>(parentItem->data(ItemTypeRole).toInt());
    if (parentType != CollectionItem) {
        qDebug() << "[SceneHierarchyModel] Can only drop onto collections";
        return false;
    }

    QString targetCollectionUuid = parentItem->data(UuidRole).toString();

    qDebug() << "[SceneHierarchyModel] Drop:" << (type == ObjectItem ? "Object" : "Collection")
             << "UUID:" << uuid << "to collection:" << targetCollectionUuid;

    // Emit signal to panel - it will handle the actual reassignment
    emit itemDropped(uuid, targetCollectionUuid, typeInt);

    // Return false so Qt doesn't modify the tree
    // The panel will rebuild the tree after reassigning collections
    return false;
}

Qt::DropActions SceneHierarchyModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

//==============================================================================
// VisibilityDelegate Implementation
//==============================================================================

VisibilityDelegate::VisibilityDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void VisibilityDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                               const QModelIndex& index) const
{
    if (index.column() == 1) {  // Visibility column
        bool visible = index.data(VisibilityRole).toBool();

        // Draw eye icon
        QRect iconRect = option.rect;
        iconRect.setLeft(iconRect.left() + 5);
        iconRect.setWidth(20);
        iconRect.setHeight(20);
        iconRect.moveCenter(option.rect.center());

        painter->save();

        if (visible) {
            // Draw visible eye icon (simplified)
            painter->setPen(QPen(Qt::black, 2));
            painter->setBrush(Qt::NoBrush);

            // Eye outline (ellipse)
            QRect eyeRect = iconRect.adjusted(2, 6, -2, -6);
            painter->drawEllipse(eyeRect);

            // Pupil
            QPoint center = eyeRect.center();
            painter->setBrush(Qt::black);
            painter->drawEllipse(center, 2, 2);
        } else {
            // Draw hidden eye icon (crossed out)
            painter->setPen(QPen(Qt::gray, 2));
            painter->drawLine(iconRect.topLeft(), iconRect.bottomRight());
            painter->drawLine(iconRect.topRight(), iconRect.bottomLeft());
        }

        painter->restore();
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

bool VisibilityDelegate::editorEvent(QEvent* event, QAbstractItemModel* model,
                                    const QStyleOptionViewItem& option,
                                    const QModelIndex& index)
{
    if (index.column() == 1 && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            emit visibilityToggled(index);
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize VisibilityDelegate::sizeHint(const QStyleOptionViewItem& option,
                                  const QModelIndex& index) const
{
    if (index.column() == 1) {
        return QSize(30, 20);
    }
    return QStyledItemDelegate::sizeHint(option, index);
}

//==============================================================================
// SceneHierarchyPanel Implementation
//==============================================================================

SceneHierarchyPanel::SceneHierarchyPanel(ObjectManager* objectManager,
                                         SelectionManager* selectionManager,
                                         QWidget* parent)
    : QWidget(parent)
    , m_objectManager(objectManager)
    , m_selectionManager(selectionManager)
    , m_sceneCollection(nullptr)
{
    setupUI();
    setupConnections();

    // Create default "Scene Collection"
    m_sceneCollection = new Collection("Scene Collection", this);

    // Add all existing objects from ObjectManager to scene collection
    if (m_objectManager) {
        for (SceneObject* obj : m_objectManager->allObjects()) {
            m_sceneCollection->addObject(obj);
        }
    }

    rebuildTree();
}

SceneHierarchyPanel::~SceneHierarchyPanel()
{
}

void SceneHierarchyPanel::setupUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    // Tree view
    m_treeView = new QTreeView(this);
    m_treeView->setHeaderHidden(false);
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_treeView->setDragEnabled(true);
    m_treeView->setAcceptDrops(true);
    m_treeView->setDropIndicatorShown(true);
    m_treeView->setDragDropMode(QAbstractItemView::InternalMove);
    m_treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeView->setExpandsOnDoubleClick(false);

    // Model
    m_model = new SceneHierarchyModel(this);
    m_model->setHorizontalHeaderLabels({"Name", "Visibility"});
    m_treeView->setModel(m_model);

    // Delegate for visibility column
    m_visibilityDelegate = new VisibilityDelegate(this);
    m_treeView->setItemDelegateForColumn(1, m_visibilityDelegate);

    // Column widths
    m_treeView->setColumnWidth(0, 200);
    m_treeView->setColumnWidth(1, 30);

    layout->addWidget(m_treeView);
}

void SceneHierarchyPanel::setupConnections()
{
    // Tree view signals
    connect(m_treeView, &QTreeView::clicked, this, &SceneHierarchyPanel::onItemClicked);
    connect(m_treeView, &QTreeView::doubleClicked, this, &SceneHierarchyPanel::onItemDoubleClicked);
    connect(m_treeView, &QTreeView::customContextMenuRequested, this, &SceneHierarchyPanel::onCustomContextMenu);

    // Visibility delegate
    connect(m_visibilityDelegate, &VisibilityDelegate::visibilityToggled,
            this, &SceneHierarchyPanel::onVisibilityToggled);

    // Model drag & drop
    connect(m_model, &SceneHierarchyModel::itemDropped,
            this, &SceneHierarchyPanel::onItemDropped);

    // ObjectManager signals
    if (m_objectManager) {
        connect(m_objectManager, &ObjectManager::objectAdded, this, &SceneHierarchyPanel::onObjectAdded);
        connect(m_objectManager, &ObjectManager::objectRemoved, this, &SceneHierarchyPanel::onObjectRemoved);
    }
}

void SceneHierarchyPanel::rebuildTree()
{
    m_model->removeRows(0, m_model->rowCount());

    if (m_sceneCollection) {
        addCollectionToTree(m_sceneCollection, m_model->invisibleRootItem());
    }

    m_treeView->expandAll();
}

void SceneHierarchyPanel::addCollectionToTree(Collection* collection, QStandardItem* parentItem)
{
    if (!collection) return;

    // Create collection item
    QStandardItem* nameItem = new QStandardItem(collection->name());
    nameItem->setData(QVariant::fromValue((void*)collection), CollectionRole);
    nameItem->setData(CollectionItem, ItemTypeRole);
    nameItem->setData(collection->uuid().toString(), UuidRole);  // Store UUID for drag & drop
    nameItem->setEditable(false);

    QStandardItem* visItem = new QStandardItem();
    visItem->setData(collection->isVisible(), VisibilityRole);
    visItem->setEditable(false);

    parentItem->appendRow({nameItem, visItem});

    // Add child collections
    for (Collection* child : collection->childCollections()) {
        addCollectionToTree(child, nameItem);
    }

    // Add objects
    for (SceneObject* obj : collection->objects()) {
        addObjectToTree(obj, nameItem);
    }
}

void SceneHierarchyPanel::addObjectToTree(SceneObject* object, QStandardItem* parentItem)
{
    if (!object) return;

    QStandardItem* nameItem = new QStandardItem(object->name());
    nameItem->setData(QVariant::fromValue((void*)object), ObjectRole);
    nameItem->setData(ObjectItem, ItemTypeRole);
    nameItem->setData(object->uuid().toString(), UuidRole);  // Store UUID for drag & drop
    nameItem->setEditable(false);

    QStandardItem* visItem = new QStandardItem();
    visItem->setData(object->isVisible(), VisibilityRole);
    visItem->setEditable(false);

    parentItem->appendRow({nameItem, visItem});
}

Collection* SceneHierarchyPanel::createCollection(const QString& name, Collection* parent)
{
    Collection* collection = new Collection(name, this);

    if (parent) {
        parent->addChildCollection(collection);
    } else {
        m_sceneCollection->addChildCollection(collection);
    }

    rebuildTree();
    emit collectionCreated(collection);

    return collection;
}

void SceneHierarchyPanel::deleteCollection(Collection* collection)
{
    if (!collection || collection == m_sceneCollection) {
        return;  // Cannot delete scene collection
    }

    // TODO: Handle objects in deleted collection

    if (collection->parentCollection()) {
        collection->parentCollection()->removeChildCollection(collection);
    }

    collection->deleteLater();
    rebuildTree();

    emit collectionDeleted(collection);
}

void SceneHierarchyPanel::onItemClicked(const QModelIndex& index)
{
    if (!index.isValid() || index.column() != 0) return;

    QStandardItem* item = m_model->itemFromIndex(index);
    if (!item) return;

    ItemType type = static_cast<ItemType>(item->data(ItemTypeRole).toInt());

    if (type == ObjectItem) {
        SceneObject* object = static_cast<SceneObject*>(item->data(ObjectRole).value<void*>());
        if (object && m_selectionManager) {
            m_selectionManager->selectObject(object, false);
            emit objectSelected(object);
        }
    }
}

void SceneHierarchyPanel::onItemDoubleClicked(const QModelIndex& index)
{
    if (!index.isValid() || index.column() != 0) return;

    QStandardItem* item = m_model->itemFromIndex(index);
    if (!item) return;

    // Toggle expand/collapse for collections
    ItemType type = static_cast<ItemType>(item->data(ItemTypeRole).toInt());
    if (type == CollectionItem) {
        m_treeView->setExpanded(index, !m_treeView->isExpanded(index));
    }
}

void SceneHierarchyPanel::onCustomContextMenu(const QPoint& pos)
{
    QModelIndex index = m_treeView->indexAt(pos);

    QMenu menu(this);

    if (index.isValid()) {
        QStandardItem* item = m_model->itemFromIndex(index);
        ItemType type = static_cast<ItemType>(item->data(ItemTypeRole).toInt());

        if (type == CollectionItem) {
            menu.addAction("New Collection", [this, item]() {
                Collection* parent = static_cast<Collection*>(item->data(CollectionRole).value<void*>());
                QString name = QInputDialog::getText(this, "New Collection", "Collection name:");
                if (!name.isEmpty()) {
                    createCollection(name, parent);
                }
            });

            // Don't allow deleting scene collection
            Collection* collection = static_cast<Collection*>(item->data(CollectionRole).value<void*>());
            if (collection != m_sceneCollection) {
                menu.addAction("Delete Collection", [this, collection]() {
                    deleteCollection(collection);
                });
            }
        } else if (type == ObjectItem) {
            menu.addAction("Delete Object", [this, item]() {
                SceneObject* object = static_cast<SceneObject*>(item->data(ObjectRole).value<void*>());
                if (object && m_objectManager) {
                    m_objectManager->removeObject(object);
                }
            });
        }
    } else {
        // Clicked on empty space
        menu.addAction("New Collection", [this]() {
            QString name = QInputDialog::getText(this, "New Collection", "Collection name:");
            if (!name.isEmpty()) {
                createCollection(name);
            }
        });
    }

    menu.exec(m_treeView->mapToGlobal(pos));
}

void SceneHierarchyPanel::onVisibilityToggled(const QModelIndex& index)
{
    if (!index.isValid()) return;

    // Get the clicked item (visibility column, column 1)
    QStandardItem* visItem = m_model->itemFromIndex(index);
    if (!visItem) return;

    // Get the corresponding name item (column 0)
    QModelIndex nameIndex = index.sibling(index.row(), 0);
    QStandardItem* nameItem = m_model->itemFromIndex(nameIndex);
    if (!nameItem) return;

    bool currentVisibility = visItem->data(VisibilityRole).toBool();
    bool newVisibility = !currentVisibility;

    ItemType type = static_cast<ItemType>(nameItem->data(ItemTypeRole).toInt());

    if (type == ObjectItem) {
        SceneObject* object = static_cast<SceneObject*>(nameItem->data(ObjectRole).value<void*>());
        if (object) {
            object->setVisible(newVisibility);
            visItem->setData(newVisibility, VisibilityRole);
            qDebug() << "[SceneHierarchyPanel] Toggled object visibility:" << object->name() << "to" << newVisibility;
        }
    } else if (type == CollectionItem) {
        Collection* collection = static_cast<Collection*>(nameItem->data(CollectionRole).value<void*>());
        if (collection) {
            collection->setVisible(newVisibility);
            qDebug() << "[SceneHierarchyPanel] Toggled collection visibility:" << collection->name() << "to" << newVisibility;
            // Rebuild tree to update all child visibilities
            rebuildTree();
        }
    }

    m_treeView->viewport()->update();
}

void SceneHierarchyPanel::onObjectAdded(SceneObject* object)
{
    if (object) {
        // Add to scene collection by default
        m_sceneCollection->addObject(object);
        rebuildTree();
    }
}

void SceneHierarchyPanel::onObjectRemoved(SceneObject* object)
{
    if (object) {
        m_sceneCollection->removeObject(object);
        rebuildTree();
    }
}

void SceneHierarchyPanel::onItemDropped(const QString& itemUuid, const QString& targetCollectionUuid, int itemType)
{
    qDebug() << "[SceneHierarchyPanel] Handling drop:" << itemUuid << "to collection:" << targetCollectionUuid;

    // Find target collection
    Collection* targetCollection = findCollectionByUuid(targetCollectionUuid, m_sceneCollection);
    if (!targetCollection) {
        qDebug() << "[SceneHierarchyPanel] Target collection not found!";
        return;
    }

    if (itemType == ObjectItem) {
        // Moving an object
        SceneObject* object = findObjectByUuid(itemUuid);
        if (!object) {
            qDebug() << "[SceneHierarchyPanel] Object not found!";
            return;
        }

        // Remove from all collections
        removeObjectFromAllCollections(object, m_sceneCollection);

        // Add to target collection
        targetCollection->addObject(object);

        qDebug() << "[SceneHierarchyPanel] Moved object" << object->name() << "to collection" << targetCollection->name();

    } else if (itemType == CollectionItem) {
        // Moving a collection
        Collection* collection = findCollectionByUuid(itemUuid, m_sceneCollection);
        if (!collection) {
            qDebug() << "[SceneHierarchyPanel] Source collection not found!";
            return;
        }

        // Can't drop a collection onto itself or its descendants
        if (collection == targetCollection || isDescendantOf(targetCollection, collection)) {
            qDebug() << "[SceneHierarchyPanel] Cannot drop collection onto itself or descendant!";
            return;
        }

        // Remove from current parent
        if (collection->parentCollection()) {
            collection->parentCollection()->removeChildCollection(collection);
        }

        // Add to target collection
        targetCollection->addChildCollection(collection);

        qDebug() << "[SceneHierarchyPanel] Moved collection" << collection->name() << "to collection" << targetCollection->name();
    }

    // Rebuild tree to show new structure
    rebuildTree();
    m_treeView->expandAll();
}

Collection* SceneHierarchyPanel::findCollectionByUuid(const QString& uuidStr, Collection* root)
{
    if (!root) {
        root = m_sceneCollection;
    }

    if (!root) {
        return nullptr;
    }

    // Check if this is the collection we're looking for
    if (root->uuid().toString() == uuidStr) {
        return root;
    }

    // Search child collections recursively
    for (Collection* child : root->childCollections()) {
        Collection* found = findCollectionByUuid(uuidStr, child);
        if (found) {
            return found;
        }
    }

    return nullptr;
}

SceneObject* SceneHierarchyPanel::findObjectByUuid(const QString& uuidStr)
{
    if (!m_objectManager) {
        return nullptr;
    }

    QUuid uuid(uuidStr);
    return m_objectManager->findByUuid(uuid);
}

void SceneHierarchyPanel::removeObjectFromAllCollections(SceneObject* object, Collection* root)
{
    if (!root) {
        return;
    }

    // Remove from this collection
    root->removeObject(object);

    // Remove from child collections recursively
    for (Collection* child : root->childCollections()) {
        removeObjectFromAllCollections(object, child);
    }
}

bool SceneHierarchyPanel::isDescendantOf(Collection* potential, Collection* ancestor)
{
    if (!potential || !ancestor) {
        return false;
    }

    Collection* current = potential->parentCollection();
    while (current) {
        if (current == ancestor) {
            return true;
        }
        current = current->parentCollection();
    }

    return false;
}

QStandardItem* SceneHierarchyPanel::findItemByObject(SceneObject* object)
{
    // TODO: Implement if needed for optimization
    return nullptr;
}

QStandardItem* SceneHierarchyPanel::findItemByCollection(Collection* collection)
{
    // TODO: Implement if needed for optimization
    return nullptr;
}
