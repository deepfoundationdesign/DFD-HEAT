#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <QObject>
#include <QVector>

class SceneObject;

/**
 * @brief Manages object and mesh element selection
 *
 * SelectionManager handles selection state for both Object Mode
 * (whole objects) and Edit Mode (vertices, edges, faces).
 */
class SelectionManager : public QObject
{
    Q_OBJECT

public:
    enum SelectionMode {
        ObjectSelection,    // Select whole objects (Object Mode)
        VertexSelection,    // Select vertices (Edit Mode)
        EdgeSelection,      // Select edges (Edit Mode)
        FaceSelection       // Select faces (Edit Mode)
    };
    Q_ENUM(SelectionMode)

    explicit SelectionManager(QObject *parent = nullptr);
    ~SelectionManager();

    // Selection mode
    SelectionMode mode() const { return m_mode; }
    void setMode(SelectionMode mode);

    // Object mode selection
    QVector<SceneObject*> selectedObjects() const { return m_selectedObjects; }
    void selectObject(SceneObject* obj, bool addToSelection = false);
    void deselectObject(SceneObject* obj);
    void clearSelection();
    bool isSelected(SceneObject* obj) const;
    int selectedObjectCount() const { return m_selectedObjects.size(); }

    // Edit mode selection (vertex/edge/face indices)
    QVector<int> selectedVertices() const { return m_selectedVertices; }
    QVector<int> selectedEdges() const { return m_selectedEdges; }
    QVector<int> selectedFaces() const { return m_selectedFaces; }

    void selectVertex(int index, bool addToSelection = false);
    void selectEdge(int index, bool addToSelection = false);
    void selectFace(int index, bool addToSelection = false);

    void deselectVertex(int index);
    void deselectEdge(int index);
    void deselectFace(int index);

    void clearVertexSelection();
    void clearEdgeSelection();
    void clearFaceSelection();

    // Convenience
    bool hasSelection() const;
    SceneObject* activeObject() const;  // First selected object

signals:
    void selectionChanged();
    void modeChanged(SelectionMode mode);

private:
    SelectionMode m_mode;

    // Object mode
    QVector<SceneObject*> m_selectedObjects;

    // Edit mode
    QVector<int> m_selectedVertices;
    QVector<int> m_selectedEdges;
    QVector<int> m_selectedFaces;
};

#endif // SELECTIONMANAGER_H
