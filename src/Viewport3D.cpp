#include "Viewport3D.h"
#include "Custom3DWindow.h"
#include "ViewportController.h"
#include "ViewportSettings.h"

#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCuboidMesh>

#include <QVBoxLayout>
#include <QWidget>

Viewport3D::Viewport3D(QWidget *parent)
    : QWidget(parent)
    , m_view(new Custom3DWindow())
    , m_rootEntity(new Qt3DCore::QEntity())
    , m_controller(std::make_unique<ViewportController>(m_view->camera()))
    , m_grid(nullptr)
    , m_axis(nullptr)
{
    // Create container widget for our custom Qt3D window
    QWidget *container = QWidget::createWindowContainer(m_view);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(container);

    m_view->setRootEntity(m_rootEntity);

    // Connect our custom window's signals to our controller
    connect(m_view, &Custom3DWindow::orbitRequested, this, &Viewport3D::onOrbitRequested);
    connect(m_view, &Custom3DWindow::panRequested, this, &Viewport3D::onPanRequested);
    connect(m_view, &Custom3DWindow::zoomRequested, this, &Viewport3D::onZoomRequested);

    setupScene();
}

Viewport3D::~Viewport3D() = default;

Qt3DRender::QCamera* Viewport3D::camera() const
{
    return m_view->camera();
}

ViewportSettings* Viewport3D::settings() const
{
    return m_controller->settings();
}

bool Viewport3D::eventFilter(QObject *obj, QEvent *event)
{
    return QWidget::eventFilter(obj, event);
}

void Viewport3D::setupScene()
{
    // Camera setup with proper settings
    ViewportSettings *settings = m_controller->settings();
    Qt3DRender::QCamera *camera = m_view->camera();
    camera->lens()->setPerspectiveProjection(
        settings->fieldOfView(),
        16.0f/9.0f,
        settings->nearPlane(),
        settings->farPlane()
    );

    // Set initial camera position
    camera->setPosition(QVector3D(10, 10, 10));
    camera->setViewCenter(QVector3D(0, 0, 0));
    camera->setUpVector(QVector3D(0, 1, 0));

    // Set background color (dark gray like Blender) - will be implemented differently

    // Setup scene elements
    setupLighting();
    createTestCube();
}

void Viewport3D::setupLighting()
{
    // Main directional light (key light)
    auto *lightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *light = new Qt3DRender::QDirectionalLight(lightEntity);
    light->setColor(QColor(255, 255, 255));  // Pure white
    light->setIntensity(1.0f);  // Increased intensity
    light->setWorldDirection(QVector3D(-0.5f, -1.0f, -0.5f).normalized());
    lightEntity->addComponent(light);

    // Ambient/fill light (softer, from opposite direction)
    auto *fillLightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *fillLight = new Qt3DRender::QDirectionalLight(fillLightEntity);
    fillLight->setColor(QColor(180, 180, 200));  // Slightly blue-ish fill
    fillLight->setIntensity(0.4f);
    fillLight->setWorldDirection(QVector3D(0.5f, 0.5f, 1.0f).normalized());
    fillLightEntity->addComponent(fillLight);

    // Add a rim light for better shape definition
    auto *rimLightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *rimLight = new Qt3DRender::QDirectionalLight(rimLightEntity);
    rimLight->setColor(QColor(255, 255, 220));  // Warm rim light
    rimLight->setIntensity(0.3f);
    rimLight->setWorldDirection(QVector3D(1.0f, 0.0f, -1.0f).normalized());
    rimLightEntity->addComponent(rimLight);
}

void Viewport3D::setupGrid()
{
    // Disabled for now
}

void Viewport3D::setupAxis()
{
    // Disabled for now
}

void Viewport3D::createTestCube()
{
    // Create a test cube (building block)
    auto *cubeEntity = new Qt3DCore::QEntity(m_rootEntity);

    // Cube mesh
    auto *cubeMesh = new Qt3DExtras::QCuboidMesh();
    cubeMesh->setXExtent(2.0f);
    cubeMesh->setYExtent(2.0f);
    cubeMesh->setZExtent(2.0f);

    // Cube material with proper lighting response
    auto *cubeMaterial = new Qt3DExtras::QPhongMaterial();
    cubeMaterial->setDiffuse(QColor(120, 150, 220));      // Light blue
    cubeMaterial->setAmbient(QColor(60, 75, 110));        // Darker ambient
    cubeMaterial->setSpecular(QColor(255, 255, 255));     // White highlights
    cubeMaterial->setShininess(50.0f);                    // Moderate shininess

    // Cube transform
    auto *cubeTransform = new Qt3DCore::QTransform();
    cubeTransform->setTranslation(QVector3D(0.0f, 1.0f, 0.0f));

    cubeEntity->addComponent(cubeMesh);
    cubeEntity->addComponent(cubeMaterial);
    cubeEntity->addComponent(cubeTransform);

    // Create a floor plane
    auto *floorEntity = new Qt3DCore::QEntity(m_rootEntity);

    auto *floorMesh = new Qt3DExtras::QCuboidMesh();
    floorMesh->setXExtent(10.0f);
    floorMesh->setYExtent(0.1f);
    floorMesh->setZExtent(10.0f);

    // Floor material
    auto *floorMaterial = new Qt3DExtras::QPhongMaterial();
    floorMaterial->setDiffuse(QColor(140, 140, 140));     // Medium gray
    floorMaterial->setAmbient(QColor(80, 80, 80));        // Darker ambient
    floorMaterial->setSpecular(QColor(200, 200, 200));    // Light specular
    floorMaterial->setShininess(20.0f);                   // Low shininess (matte)

    auto *floorTransform = new Qt3DCore::QTransform();
    floorTransform->setTranslation(QVector3D(0.0f, -0.05f, 0.0f));

    floorEntity->addComponent(floorMesh);
    floorEntity->addComponent(floorMaterial);
    floorEntity->addComponent(floorTransform);

    // Add a second cube for comparison
    auto *cube2Entity = new Qt3DCore::QEntity(m_rootEntity);

    auto *cube2Mesh = new Qt3DExtras::QCuboidMesh();
    cube2Mesh->setXExtent(1.5f);
    cube2Mesh->setYExtent(3.0f);
    cube2Mesh->setZExtent(1.0f);

    // Different material for the second cube
    auto *cube2Material = new Qt3DExtras::QPhongMaterial();
    cube2Material->setDiffuse(QColor(220, 120, 100));     // Orange-red
    cube2Material->setAmbient(QColor(110, 60, 50));       // Darker ambient
    cube2Material->setSpecular(QColor(255, 255, 255));    // White highlights
    cube2Material->setShininess(80.0f);                   // Higher shininess

    auto *cube2Transform = new Qt3DCore::QTransform();
    cube2Transform->setTranslation(QVector3D(3.0f, 1.5f, 0.0f));

    cube2Entity->addComponent(cube2Mesh);
    cube2Entity->addComponent(cube2Material);
    cube2Entity->addComponent(cube2Transform);
}

void Viewport3D::onOrbitRequested(int deltaX, int deltaY)
{
    // Convert to QPoint for compatibility with ViewportController
    QPoint currentPos(deltaX, deltaY);
    QPoint lastPos(0, 0);

    m_controller->startOrbit(lastPos);
    m_controller->orbit(currentPos);
}

void Viewport3D::onPanRequested(int deltaX, int deltaY)
{
    // Convert to QPoint for compatibility with ViewportController
    QPoint currentPos(deltaX, deltaY);
    QPoint lastPos(0, 0);

    m_controller->startPan(lastPos);
    m_controller->pan(currentPos);
}

void Viewport3D::onZoomRequested(float delta)
{
    m_controller->zoom(delta);
}