#include "scene/SelectionManager.h"
#include "scene/SceneObject.h"
#include <QDebug>

SelectionManager::SelectionManager(QObject *parent)
    : QObject(parent)
    , m_mode(ObjectSelection)
{
    qDebug() << "SelectionManager created";
}

SelectionManager::~SelectionManager()
{
}

void SelectionManager::setMode(SelectionMode mode)
{
    if (m_mode == mode)
        return;

    qDebug() << "Selection mode changed to:" << mode;
    m_mode = mode;
    emit modeChanged(m_mode);
}

void SelectionManager::selectObject(SceneObject* obj, bool addToSelection)
{
    if (!obj) {
        qWarning() << "Cannot select null object";
        return;
    }

    // Clear previous selection if not adding
    if (!addToSelection) {
        for (SceneObject* prevObj : m_selectedObjects) {
            prevObj->setSelected(false);
        }
        m_selectedObjects.clear();
    }

    // Add to selection if not already selected
    if (!m_selectedObjects.contains(obj)) {
        m_selectedObjects.append(obj);
        obj->setSelected(true);
        qDebug() << "Object selected:" << obj->name() << "Total selected:" << m_selectedObjects.size();
        emit selectionChanged();
    }
}

void SelectionManager::deselectObject(SceneObject* obj)
{
    if (!obj) return;

    int index = m_selectedObjects.indexOf(obj);
    if (index != -1) {
        m_selectedObjects.removeAt(index);
        obj->setSelected(false);
        qDebug() << "Object deselected:" << obj->name();
        emit selectionChanged();
    }
}

void SelectionManager::clearSelection()
{
    if (m_selectedObjects.isEmpty())
        return;

    for (SceneObject* obj : m_selectedObjects) {
        obj->setSelected(false);
    }

    m_selectedObjects.clear();
    qDebug() << "Selection cleared";
    emit selectionChanged();
}

bool SelectionManager::isSelected(SceneObject* obj) const
{
    return m_selectedObjects.contains(obj);
}

void SelectionManager::selectVertex(int index, bool addToSelection)
{
    if (!addToSelection) {
        m_selectedVertices.clear();
    }

    if (!m_selectedVertices.contains(index)) {
        m_selectedVertices.append(index);
        emit selectionChanged();
    }
}

void SelectionManager::selectEdge(int index, bool addToSelection)
{
    if (!addToSelection) {
        m_selectedEdges.clear();
    }

    if (!m_selectedEdges.contains(index)) {
        m_selectedEdges.append(index);
        emit selectionChanged();
    }
}

void SelectionManager::selectFace(int index, bool addToSelection)
{
    if (!addToSelection) {
        m_selectedFaces.clear();
    }

    if (!m_selectedFaces.contains(index)) {
        m_selectedFaces.append(index);
        emit selectionChanged();
    }
}

void SelectionManager::deselectVertex(int index)
{
    m_selectedVertices.removeAll(index);
    emit selectionChanged();
}

void SelectionManager::deselectEdge(int index)
{
    m_selectedEdges.removeAll(index);
    emit selectionChanged();
}

void SelectionManager::deselectFace(int index)
{
    m_selectedFaces.removeAll(index);
    emit selectionChanged();
}

void SelectionManager::clearVertexSelection()
{
    if (!m_selectedVertices.isEmpty()) {
        m_selectedVertices.clear();
        emit selectionChanged();
    }
}

void SelectionManager::clearEdgeSelection()
{
    if (!m_selectedEdges.isEmpty()) {
        m_selectedEdges.clear();
        emit selectionChanged();
    }
}

void SelectionManager::clearFaceSelection()
{
    if (!m_selectedFaces.isEmpty()) {
        m_selectedFaces.clear();
        emit selectionChanged();
    }
}

bool SelectionManager::hasSelection() const
{
    return !m_selectedObjects.isEmpty() ||
           !m_selectedVertices.isEmpty() ||
           !m_selectedEdges.isEmpty() ||
           !m_selectedFaces.isEmpty();
}

SceneObject* SelectionManager::activeObject() const
{
    return m_selectedObjects.isEmpty() ? nullptr : m_selectedObjects.first();
}
