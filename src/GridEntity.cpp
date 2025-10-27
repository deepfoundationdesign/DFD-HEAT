#include "GridEntity.h"

#include <Qt3DCore/QGeometry>
#include <Qt3DCore/QAttribute>
#include <Qt3DCore/QBuffer>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPerVertexColorMaterial>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QGraphicsApiFilter>

GridEntity::GridEntity(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , m_gridSize(1.0f)
    , m_gridDivisions(20)
    , m_color(128, 128, 128, 100)
{
    createGrid();
}

GridEntity::~GridEntity() = default;

void GridEntity::setGridSize(float size)
{
    if (!qFuzzyCompare(m_gridSize, size)) {
        m_gridSize = size;
        createGrid();
    }
}

void GridEntity::setGridDivisions(int divisions)
{
    if (m_gridDivisions != divisions) {
        m_gridDivisions = divisions;
        createGrid();
    }
}

void GridEntity::setColor(const QColor &color)
{
    if (m_color != color) {
        m_color = color;
        if (m_material) {
            auto phongMat = qobject_cast<Qt3DExtras::QPhongMaterial*>(m_material);
            if (phongMat) {
                phongMat->setDiffuse(m_color);
                phongMat->setAmbient(m_color);
            }
        }
    }
}

void GridEntity::setVisible(bool visible)
{
    setEnabled(visible);
}

void GridEntity::createGrid()
{
    // Remove old components
    if (m_mesh) {
        removeComponent(m_mesh);
        delete m_mesh;
    }
    if (m_material) {
        removeComponent(m_material);
        delete m_material;
    }

    // Create geometry for grid lines
    auto *geometry = new Qt3DCore::QGeometry(this);

    // Calculate grid dimensions
    float halfSize = (m_gridDivisions * m_gridSize) / 2.0f;
    int lineCount = m_gridDivisions + 1;

    // Vertices for grid lines (2 vertices per line)
    QByteArray vertexBytes;
    vertexBytes.resize(lineCount * 4 * 3 * sizeof(float)); // X and Z lines, 3 floats per vertex
    float *vertices = reinterpret_cast<float*>(vertexBytes.data());

    int idx = 0;

    // Create lines parallel to X axis
    for (int i = 0; i < lineCount; ++i) {
        float z = -halfSize + i * m_gridSize;

        // Start point
        vertices[idx++] = -halfSize;
        vertices[idx++] = 0.0f;
        vertices[idx++] = z;

        // End point
        vertices[idx++] = halfSize;
        vertices[idx++] = 0.0f;
        vertices[idx++] = z;
    }

    // Create lines parallel to Z axis
    for (int i = 0; i < lineCount; ++i) {
        float x = -halfSize + i * m_gridSize;

        // Start point
        vertices[idx++] = x;
        vertices[idx++] = 0.0f;
        vertices[idx++] = -halfSize;

        // End point
        vertices[idx++] = x;
        vertices[idx++] = 0.0f;
        vertices[idx++] = halfSize;
    }

    // Create vertex buffer
    auto *vertexBuffer = new Qt3DCore::QBuffer(geometry);
    vertexBuffer->setData(vertexBytes);

    // Create position attribute
    auto *positionAttribute = new Qt3DCore::QAttribute(geometry);
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(vertexBuffer);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(lineCount * 4);

    geometry->addAttribute(positionAttribute);

    // Create geometry renderer
    m_mesh = new Qt3DRender::QGeometryRenderer(this);
    m_mesh->setGeometry(geometry);
    m_mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);

    // Create material
    m_material = new Qt3DExtras::QPhongMaterial(this);
    auto phongMat = qobject_cast<Qt3DExtras::QPhongMaterial*>(m_material);
    phongMat->setDiffuse(m_color);
    phongMat->setAmbient(m_color);
    phongMat->setSpecular(QColor(0, 0, 0));
    phongMat->setShininess(0.0f);

    // Add components
    addComponent(m_mesh);
    addComponent(m_material);
}