#include "BoxObject.h"
#include "MeshData.h"
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <QDebug>

BoxObject::BoxObject(Qt3DCore::QNode *parent)
    : SceneObject(parent)
{
    setName("Box");
    initialize();
}

BoxObject::BoxObject(float width, float height, float depth, Qt3DCore::QNode *parent)
    : SceneObject(parent)
{
    setName("Box");
    setDimensions(QVector3D(width, height, depth));
    initialize();
}

BoxObject::~BoxObject()
{
}

void BoxObject::initialize()
{
    // Create material
    auto* material = new Qt3DExtras::QPhongMaterial(this);
    material->setDiffuse(QColor(120, 150, 220));      // Blue
    material->setAmbient(QColor(60, 75, 110));
    material->setSpecular(QColor(255, 255, 255));
    material->setShininess(50.0f);
    m_material = material;
    addComponent(m_material);

    // Create geometry renderer
    m_renderer = new Qt3DRender::QGeometryRenderer(this);
    m_renderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
    addComponent(m_renderer);

    // Generate initial mesh
    generateMesh();
    updateGeometry();

    qDebug() << "BoxObject initialized with dimensions:" << dimensions();
}

void BoxObject::setDimensions(const QVector3D& dim)
{
    SceneObject::setDimensions(dim);
}

void BoxObject::setDimensions(float width, float height, float depth)
{
    setDimensions(QVector3D(width, height, depth));
}

void BoxObject::generateMesh()
{
    m_meshData->clear();

    float w = dimensions().x() / 2.0f;  // Half-width
    float h = dimensions().y() / 2.0f;  // Half-height
    float d = dimensions().z() / 2.0f;  // Half-depth

    // Create 8 vertices of a box (centered at origin)
    int v0 = m_meshData->addVertex(QVector3D(-w, -h, -d));  // Bottom-back-left
    int v1 = m_meshData->addVertex(QVector3D( w, -h, -d));  // Bottom-back-right
    int v2 = m_meshData->addVertex(QVector3D( w, -h,  d));  // Bottom-front-right
    int v3 = m_meshData->addVertex(QVector3D(-w, -h,  d));  // Bottom-front-left
    int v4 = m_meshData->addVertex(QVector3D(-w,  h, -d));  // Top-back-left
    int v5 = m_meshData->addVertex(QVector3D( w,  h, -d));  // Top-back-right
    int v6 = m_meshData->addVertex(QVector3D( w,  h,  d));  // Top-front-right
    int v7 = m_meshData->addVertex(QVector3D(-w,  h,  d));  // Top-front-left

    // Create 6 faces (quads, counter-clockwise winding)
    // Bottom face (Y-)
    m_meshData->addFace({v0, v1, v2, v3});

    // Top face (Y+)
    m_meshData->addFace({v4, v7, v6, v5});

    // Front face (Z+)
    m_meshData->addFace({v3, v2, v6, v7});

    // Back face (Z-)
    m_meshData->addFace({v1, v0, v4, v5});

    // Left face (X-)
    m_meshData->addFace({v0, v3, v7, v4});

    // Right face (X+)
    m_meshData->addFace({v2, v1, v5, v6});

    qDebug() << "Box mesh generated:"
             << m_meshData->vertexCount() << "vertices,"
             << m_meshData->faceCount() << "faces";
}
