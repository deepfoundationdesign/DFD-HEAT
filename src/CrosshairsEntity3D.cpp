#include "CrosshairsEntity3D.h"

#include <Qt3DCore/QTransform>
#include <Qt3DCore/QGeometry>
#include <Qt3DCore/QBuffer>
#include <Qt3DCore/QAttribute>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QLayer>
#include <Qt3DExtras/QPhongMaterial>

#include <QVector3D>
#include <QDebug>

CrosshairsEntity3D::CrosshairsEntity3D(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , m_geometry(new Qt3DCore::QGeometry(this))
    , m_renderer(new Qt3DRender::QGeometryRenderer(this))
    , m_material(new Qt3DExtras::QPhongMaterial(this))
    , m_transform(new Qt3DCore::QTransform(this))
    , m_crosshairSize(0.05f)  // Size in normalized device coordinates
    , m_gap(0.01f)            // Gap in normalized device coordinates
{
    createCrosshairsGeometry();

    // Setup renderer
    m_renderer->setGeometry(m_geometry);
    m_renderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);

    // Setup material - bright white for visibility
    m_material->setDiffuse(QColor(255, 255, 255));
    m_material->setAmbient(QColor(255, 255, 255));
    m_material->setSpecular(QColor(255, 255, 255));
    m_material->setShininess(0.0f);

    // Add components to entity
    addComponent(m_renderer);
    addComponent(m_material);
    addComponent(m_transform);

    qDebug() << "[CrosshairsEntity3D] Created crosshairs entity";
}

void CrosshairsEntity3D::setLayer(Qt3DRender::QLayer* layer)
{
    if (layer) {
        addComponent(layer);
        qDebug() << "[CrosshairsEntity3D] Added to HUD layer";
    }
}

void CrosshairsEntity3D::setVisible(bool visible)
{
    setEnabled(visible);
    qDebug() << "[CrosshairsEntity3D] Visibility set to:" << visible;
}

void CrosshairsEntity3D::createCrosshairsGeometry()
{
    // Create crosshairs as 4 line segments in screen space (Z = 0)
    // Horizontal line (left and right of center)
    // Vertical line (top and bottom of center)

    QVector<QVector3D> vertices;

    // Horizontal line - left segment
    vertices << QVector3D(-m_crosshairSize, 0, 0) << QVector3D(-m_gap, 0, 0);
    // Horizontal line - right segment
    vertices << QVector3D(m_gap, 0, 0) << QVector3D(m_crosshairSize, 0, 0);
    // Vertical line - bottom segment
    vertices << QVector3D(0, -m_crosshairSize, 0) << QVector3D(0, -m_gap, 0);
    // Vertical line - top segment
    vertices << QVector3D(0, m_gap, 0) << QVector3D(0, m_crosshairSize, 0);

    // Create vertex buffer
    QByteArray vertexBufferData;
    vertexBufferData.resize(vertices.size() * 3 * sizeof(float));
    float *rawVertexArray = reinterpret_cast<float*>(vertexBufferData.data());

    for (int i = 0; i < vertices.size(); ++i) {
        rawVertexArray[i * 3 + 0] = vertices[i].x();
        rawVertexArray[i * 3 + 1] = vertices[i].y();
        rawVertexArray[i * 3 + 2] = vertices[i].z();
    }

    auto *vertexBuffer = new Qt3DCore::QBuffer(m_geometry);
    vertexBuffer->setData(vertexBufferData);

    // Position attribute
    auto *positionAttribute = new Qt3DCore::QAttribute(m_geometry);
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(vertexBuffer);
    positionAttribute->setByteOffset(0);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(vertices.size());

    m_geometry->addAttribute(positionAttribute);

    qDebug() << "[CrosshairsEntity3D] Created geometry with" << vertices.size() << "vertices (4 line segments)";
}
