#include "entities/AxisEntity.h"

#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QGeometry>
#include <Qt3DCore/QAttribute>
#include <Qt3DCore/QBuffer>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QDepthTest>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QGraphicsApiFilter>
#include <QDebug>

AxisEntity::AxisEntity(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , m_length(1000.0f)  // Extends towards "infinity"
    , m_thickness(0.1f)  // Thicker lines for better visibility
    , m_xAxis(nullptr)
    , m_yAxis(nullptr)
    , m_zAxis(nullptr)
{
    createAxis();
}

AxisEntity::~AxisEntity() = default;

// Helper function to create an always-on-top material by modifying QPhongMaterial
static Qt3DRender::QMaterial* createAlwaysOnTopMaterial(const QColor &color, Qt3DCore::QNode *parent)
{
    // Get a standard phong material
    auto *phongMaterial = new Qt3DExtras::QPhongMaterial(parent);
    phongMaterial->setDiffuse(color);
    phongMaterial->setAmbient(color.lighter(150));
    phongMaterial->setSpecular(QColor(255, 255, 255));
    phongMaterial->setShininess(100.0f);

    // Access the effect and modify all render passes to add QDepthTest with Always
    auto *effect = phongMaterial->effect();
    for (auto *technique : effect->techniques()) {
        for (auto *renderPass : technique->renderPasses()) {
            // Add depth test with Always function
            auto *depthTest = new Qt3DRender::QDepthTest(renderPass);
            depthTest->setDepthFunction(Qt3DRender::QDepthTest::Always);
            renderPass->addRenderState(depthTest);
        }
    }

    return phongMaterial;
}

void AxisEntity::setLength(float length)
{
    if (!qFuzzyCompare(m_length, length)) {
        m_length = length;
        createAxis();
    }
}

void AxisEntity::setThickness(float thickness)
{
    if (!qFuzzyCompare(m_thickness, thickness)) {
        m_thickness = thickness;
        createAxis();
    }
}

void AxisEntity::setVisible(bool visible)
{
    setEnabled(visible);
}

void AxisEntity::createAxis()
{
    // Remove old axis entities
    if (m_xAxis) {
        m_xAxis->deleteLater();
    }
    if (m_yAxis) {
        m_yAxis->deleteLater();
    }
    if (m_zAxis) {
        m_zAxis->deleteLater();
    }

    // Create X axis (RED) - horizontal along X
    m_xAxis = createAxisLine(QVector3D(1, 0, 0), QColor(255, 0, 0));

    // Create Y axis (GREEN) - horizontal along Z (since Qt3D Y is vertical)
    m_yAxis = createAxisLine(QVector3D(0, 0, 1), QColor(0, 255, 0));

    // Z axis not created - Qt3D Y-axis is vertical, user only wants horizontal X and Y
    m_zAxis = nullptr;
}

Qt3DCore::QEntity* AxisEntity::createAxisLine(const QVector3D &direction, const QColor &color)
{
    auto *axisEntity = new Qt3DCore::QEntity(this);

    // Create line geometry
    auto *geometry = new Qt3DCore::QGeometry(axisEntity);

    // Create vertices for the line
    QByteArray vertexBytes;
    vertexBytes.resize(2 * 3 * sizeof(float)); // 2 vertices, 3 floats each
    float *vertices = reinterpret_cast<float*>(vertexBytes.data());

    // Line from origin to direction * length
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    vertices[3] = direction.x() * m_length;
    vertices[4] = direction.y() * m_length;
    vertices[5] = direction.z() * m_length;

    // Also create negative direction
    QByteArray negVertexBytes;
    negVertexBytes.resize(2 * 3 * sizeof(float));
    float *negVertices = reinterpret_cast<float*>(negVertexBytes.data());

    negVertices[0] = 0.0f;
    negVertices[1] = 0.0f;
    negVertices[2] = 0.0f;

    negVertices[3] = -direction.x() * m_length;
    negVertices[4] = -direction.y() * m_length;
    negVertices[5] = -direction.z() * m_length;

    // Combine both directions
    QByteArray combinedBytes;
    combinedBytes.append(vertexBytes);
    combinedBytes.append(negVertexBytes);

    // Create vertex buffer
    auto *vertexBuffer = new Qt3DCore::QBuffer(geometry);
    vertexBuffer->setData(combinedBytes);

    // Create position attribute
    auto *positionAttribute = new Qt3DCore::QAttribute(geometry);
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(vertexBuffer);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(4);

    geometry->addAttribute(positionAttribute);

    // Create geometry renderer
    auto *lineRenderer = new Qt3DRender::QGeometryRenderer(axisEntity);
    lineRenderer->setGeometry(geometry);
    lineRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    lineRenderer->setVertexCount(4);

    // Create material with always-on-top depth test
    auto *material = createAlwaysOnTopMaterial(color, axisEntity);

    // Add components
    axisEntity->addComponent(lineRenderer);
    axisEntity->addComponent(material);

    // Add arrow head (cone) at positive end
    auto *arrowEntity = new Qt3DCore::QEntity(axisEntity);

    auto *arrowMesh = new Qt3DExtras::QConeMesh();
    arrowMesh->setBottomRadius(m_thickness * 3);
    arrowMesh->setTopRadius(0.0f);
    arrowMesh->setLength(m_thickness * 10);
    arrowMesh->setRings(8);
    arrowMesh->setSlices(8);

    auto *arrowTransform = new Qt3DCore::QTransform();
    QVector3D arrowPos = direction * (m_length - m_thickness * 5);
    arrowTransform->setTranslation(arrowPos);

    // Rotate arrow to point in the right direction
    if (direction == QVector3D(1, 0, 0)) {
        arrowTransform->setRotationZ(90);
    } else if (direction == QVector3D(0, 1, 0)) {
        // Y axis - default orientation
    } else if (direction == QVector3D(0, 0, 1)) {
        arrowTransform->setRotationX(-90);
    }

    // Create material for arrow with always-on-top depth test
    auto *arrowMaterial = createAlwaysOnTopMaterial(color, arrowEntity);

    arrowEntity->addComponent(arrowMesh);
    arrowEntity->addComponent(arrowTransform);
    arrowEntity->addComponent(arrowMaterial);

    return axisEntity;
}