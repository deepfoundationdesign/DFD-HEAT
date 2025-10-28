#ifndef MESHDATA_H
#define MESHDATA_H

#include <QVector>
#include <QVector3D>

namespace Qt3DCore {
    class QNode;
    class QGeometry;
    class QAttribute;
    class QBuffer;
}

/**
 * @brief Stores mesh geometry data (vertices, edges, faces)
 *
 * MeshData provides a structured representation of 3D geometry that can be
 * manipulated in Edit Mode and converted to Qt3D geometry for rendering.
 */
class MeshData
{
public:
    struct Vertex {
        QVector3D position;
        int index;

        Vertex() : index(-1) {}
        Vertex(const QVector3D& pos, int idx) : position(pos), index(idx) {}
    };

    struct Edge {
        int v0, v1;  // Vertex indices
        int index;

        Edge() : v0(-1), v1(-1), index(-1) {}
        Edge(int vertex0, int vertex1, int idx) : v0(vertex0), v1(vertex1), index(idx) {}
    };

    struct Face {
        QVector<int> vertices;  // Vertex indices (ordered counter-clockwise)
        QVector<int> edges;     // Edge indices
        int index;

        Face() : index(-1) {}
        Face(const QVector<int>& verts, int idx) : vertices(verts), index(idx) {}
    };

    MeshData();
    ~MeshData();

    // Vertex operations
    int addVertex(const QVector3D& position);
    void removeVertex(int index);
    void updateVertex(int index, const QVector3D& position);
    const QVector<Vertex>& getVertices() const { return m_vertices; }
    int vertexCount() const { return m_vertices.size(); }

    // Edge operations
    int addEdge(int v0, int v1);
    void removeEdge(int index);
    const QVector<Edge>& getEdges() const { return m_edges; }
    int edgeCount() const { return m_edges.size(); }

    // Face operations
    int addFace(const QVector<int>& vertexIndices);
    void removeFace(int index);
    const QVector<Face>& getFaces() const { return m_faces; }
    int faceCount() const { return m_faces.size(); }

    // Geometry generation for Qt3D rendering
    Qt3DCore::QGeometry* generateGeometry(Qt3DCore::QNode* parent = nullptr);

    // Clear all data
    void clear();

    // Utility
    bool isValid() const;

private:
    QVector<Vertex> m_vertices;
    QVector<Edge> m_edges;
    QVector<Face> m_faces;

    int m_nextVertexIndex;
    int m_nextEdgeIndex;
    int m_nextFaceIndex;

    // Helper methods
    void buildEdgesFromFaces();
    int findOrCreateEdge(int v0, int v1);
};

#endif // MESHDATA_H
