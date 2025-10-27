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

    // Camera is now controlled by our ViewportController
    // which handles Blender-style navigation

    // Setup scene elements
    setupLighting();
    createTestCube();
}

void Viewport3D::setupLighting()
{
    // Main directional light
    auto *lightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *light = new Qt3DRender::QDirectionalLight(lightEntity);
    light->setColor("white");
    light->setIntensity(0.7f);
    light->setWorldDirection(QVector3D(-1, -1, -1).normalized());
    lightEntity->addComponent(light);

    // Fill light
    auto *fillLightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *fillLight = new Qt3DRender::QDirectionalLight(fillLightEntity);
    fillLight->setColor(QColor(100, 100, 100));
    fillLight->setIntensity(0.3f);
    fillLight->setWorldDirection(QVector3D(1, 0.5f, 0.5f).normalized());
    fillLightEntity->addComponent(fillLight);
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
    // Create a simple test cube
    auto *cubeEntity = new Qt3DCore::QEntity(m_rootEntity);

    // Cube mesh
    auto *cubeMesh = new Qt3DExtras::QCuboidMesh();
    cubeMesh->setXExtent(2.0f);
    cubeMesh->setYExtent(2.0f);
    cubeMesh->setZExtent(2.0f);

    // Cube material
    auto *cubeMaterial = new Qt3DExtras::QPhongMaterial();
    cubeMaterial->setDiffuse(QColor(100, 100, 200));

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

    auto *floorMaterial = new Qt3DExtras::QPhongMaterial();
    floorMaterial->setDiffuse(QColor(120, 120, 120));

    auto *floorTransform = new Qt3DCore::QTransform();
    floorTransform->setTranslation(QVector3D(0.0f, -0.05f, 0.0f));

    floorEntity->addComponent(floorMesh);
    floorEntity->addComponent(floorMaterial);
    floorEntity->addComponent(floorTransform);
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