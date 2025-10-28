#include "mesh/MeshData.h"
#include <Qt3DCore/QGeometry>
#include <Qt3DCore/QAttribute>
#include <Qt3DCore/QBuffer>
#include <QDebug>

MeshData::MeshData()
    : m_nextVertexIndex(0)
    , m_nextEdgeIndex(0)
    , m_nextFaceIndex(0)
{
}

MeshData::~MeshData()
{
}

int MeshData::addVertex(const QVector3D& position)
{
    int index = m_nextVertexIndex++;
    m_vertices.append(Vertex(position, index));
    return index;
}

void MeshData::removeVertex(int index)
{
    // Find and remove the vertex
    for (int i = 0; i < m_vertices.size(); ++i) {
        if (m_vertices[i].index == index) {
            m_vertices.removeAt(i);
            break;
        }
    }

    // Remove any edges that reference this vertex
    for (int i = m_edges.size() - 1; i >= 0; --i) {
        if (m_edges[i].v0 == index || m_edges[i].v1 == index) {
            m_edges.removeAt(i);
        }
    }

    // Remove any faces that reference this vertex
    for (int i = m_faces.size() - 1; i >= 0; --i) {
        if (m_faces[i].vertices.contains(index)) {
            m_faces.removeAt(i);
        }
    }
}

void MeshData::updateVertex(int index, const QVector3D& position)
{
    for (int i = 0; i < m_vertices.size(); ++i) {
        if (m_vertices[i].index == index) {
            m_vertices[i].position = position;
            return;
        }
    }
}

int MeshData::addEdge(int v0, int v1)
{
    // Check if edge already exists
    for (const Edge& edge : m_edges) {
        if ((edge.v0 == v0 && edge.v1 == v1) || (edge.v0 == v1 && edge.v1 == v0)) {
            return edge.index;
        }
    }

    int index = m_nextEdgeIndex++;
    m_edges.append(Edge(v0, v1, index));
    return index;
}

void MeshData::removeEdge(int index)
{
    for (int i = 0; i < m_edges.size(); ++i) {
        if (m_edges[i].index == index) {
            m_edges.removeAt(i);
            break;
        }
    }
}

int MeshData::addFace(const QVector<int>& vertexIndices)
{
    if (vertexIndices.size() < 3) {
        qWarning() << "Cannot create face with less than 3 vertices";
        return -1;
    }

    int index = m_nextFaceIndex++;
    Face face(vertexIndices, index);

    // Create edges for this face
    for (int i = 0; i < vertexIndices.size(); ++i) {
        int v0 = vertexIndices[i];
        int v1 = vertexIndices[(i + 1) % vertexIndices.size()];
        int edgeIdx = findOrCreateEdge(v0, v1);
        face.edges.append(edgeIdx);
    }

    m_faces.append(face);
    return index;
}

void MeshData::removeFace(int index)
{
    for (int i = 0; i < m_faces.size(); ++i) {
        if (m_faces[i].index == index) {
            m_faces.removeAt(i);
            break;
        }
    }
}

Qt3DCore::QGeometry* MeshData::generateGeometry(Qt3DCore::QNode* parent)
{
    if (m_faces.isEmpty() || m_vertices.isEmpty()) {
        qWarning() << "Cannot generate geometry: No faces or vertices";
        return nullptr;
    }

    // Build arrays for rendering
    QVector<QVector3D> positions;
    QVector<QVector3D> normals;
    QVector<unsigned int> indices;

    // Generate triangulated mesh from faces
    for (const Face& face : m_faces) {
        if (face.vertices.size() < 3) continue;

        // Simple fan triangulation for n-gons
        int v0Idx = face.vertices[0];
        QVector3D v0;
        for (const Vertex& v : m_vertices) {
            if (v.index == v0Idx) {
                v0 = v.position;
                break;
            }
        }

        for (int i = 1; i < face.vertices.size() - 1; ++i) {
            // Find vertex positions
            QVector3D v1, v2;
            for (const Vertex& v : m_vertices) {
                if (v.index == face.vertices[i]) v1 = v.position;
                if (v.index == face.vertices[i + 1]) v2 = v.position;
            }

            // Calculate face normal
            QVector3D edge1 = v1 - v0;
            QVector3D edge2 = v2 - v0;
            QVector3D normal = QVector3D::crossProduct(edge1, edge2).normalized();

            // Add triangle
            unsigned int baseIdx = positions.size();
            positions.append(v0);
            positions.append(v1);
            positions.append(v2);
            normals.append(normal);
            normals.append(normal);
            normals.append(normal);
            indices.append(baseIdx);
            indices.append(baseIdx + 1);
            indices.append(baseIdx + 2);
        }
    }

    // Create Qt3D geometry
    auto* geometry = new Qt3DCore::QGeometry(parent);

    // Position attribute
    auto* positionBuffer = new Qt3DCore::QBuffer(geometry);
    QByteArray positionData;
    positionData.resize(positions.size() * 3 * sizeof(float));
    float* posPtr = reinterpret_cast<float*>(positionData.data());
    for (const QVector3D& pos : positions) {
        *posPtr++ = pos.x();
        *posPtr++ = pos.y();
        *posPtr++ = pos.z();
    }
    positionBuffer->setData(positionData);

    auto* positionAttribute = new Qt3DCore::QAttribute(geometry);
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(positionBuffer);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(positions.size());
    geometry->addAttribute(positionAttribute);

    // Normal attribute
    auto* normalBuffer = new Qt3DCore::QBuffer(geometry);
    QByteArray normalData;
    normalData.resize(normals.size() * 3 * sizeof(float));
    float* normPtr = reinterpret_cast<float*>(normalData.data());
    for (const QVector3D& norm : normals) {
        *normPtr++ = norm.x();
        *normPtr++ = norm.y();
        *normPtr++ = norm.z();
    }
    normalBuffer->setData(normalData);

    auto* normalAttribute = new Qt3DCore::QAttribute(geometry);
    normalAttribute->setName(Qt3DCore::QAttribute::defaultNormalAttributeName());
    normalAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    normalAttribute->setVertexSize(3);
    normalAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    normalAttribute->setBuffer(normalBuffer);
    normalAttribute->setByteStride(3 * sizeof(float));
    normalAttribute->setCount(normals.size());
    geometry->addAttribute(normalAttribute);

    // Index attribute
    auto* indexBuffer = new Qt3DCore::QBuffer(geometry);
    QByteArray indexData;
    indexData.resize(indices.size() * sizeof(unsigned int));
    unsigned int* idxPtr = reinterpret_cast<unsigned int*>(indexData.data());
    for (unsigned int idx : indices) {
        *idxPtr++ = idx;
    }
    indexBuffer->setData(indexData);

    auto* indexAttribute = new Qt3DCore::QAttribute(geometry);
    indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedInt);
    indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
    indexAttribute->setBuffer(indexBuffer);
    indexAttribute->setCount(indices.size());
    geometry->addAttribute(indexAttribute);

    return geometry;
}

void MeshData::clear()
{
    m_vertices.clear();
    m_edges.clear();
    m_faces.clear();
    m_nextVertexIndex = 0;
    m_nextEdgeIndex = 0;
    m_nextFaceIndex = 0;
}

bool MeshData::isValid() const
{
    return !m_vertices.isEmpty() && !m_faces.isEmpty();
}

int MeshData::findOrCreateEdge(int v0, int v1)
{
    // Check if edge already exists (in either direction)
    for (const Edge& edge : m_edges) {
        if ((edge.v0 == v0 && edge.v1 == v1) || (edge.v0 == v1 && edge.v1 == v0)) {
            return edge.index;
        }
    }

    // Create new edge
    return addEdge(v0, v1);
}

void MeshData::buildEdgesFromFaces()
{
    m_edges.clear();
    m_nextEdgeIndex = 0;

    for (const Face& face : m_faces) {
        for (int i = 0; i < face.vertices.size(); ++i) {
            int v0 = face.vertices[i];
            int v1 = face.vertices[(i + 1) % face.vertices.size()];
            findOrCreateEdge(v0, v1);
        }
    }
}
