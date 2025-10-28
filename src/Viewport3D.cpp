#include "Viewport3D.h"
#include "Custom3DWindow.h"
#include "ViewportController.h"
#include "ViewportSettings.h"
#include "GridEntity.h"
#include "AxisEntity.h"
#include "ModeManager.h"
#include "ObjectManager.h"
#include "SelectionManager.h"
#include "SceneObject.h"
#include "BoxObject.h"

#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCuboidMesh>

#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>

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
    setupGrid();
    setupAxis();
    setupObjectSystem();
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
    if (!m_grid) {
        m_grid = new GridEntity(m_rootEntity);
        ViewportSettings *settings = m_controller->settings();
        m_grid->setGridSize(settings->gridSize());
        m_grid->setGridDivisions(settings->gridDivisions());
        m_grid->setColor(settings->gridColor());
        m_grid->setVisible(settings->showGrid());
    }
}

void Viewport3D::setupAxis()
{
    if (!m_axis) {
        m_axis = new AxisEntity(m_rootEntity);
        ViewportSettings *settings = m_controller->settings();
        m_axis->setLength(settings->axisLength());
        m_axis->setThickness(settings->axisThickness());
        m_axis->setVisible(settings->showAxis());
    }
}

void Viewport3D::setupObjectSystem()
{
    // Create object management system
    m_modeManager = std::make_unique<ModeManager>(this);
    m_objectManager = std::make_unique<ObjectManager>(m_rootEntity, this);
    m_selectionManager = std::make_unique<SelectionManager>(this);

    // Connect ObjectManager signals to handle new objects
    connect(m_objectManager.get(), &ObjectManager::objectAdded,
            this, &Viewport3D::onObjectAdded);

    qDebug() << "Object system initialized";
}

void Viewport3D::createBox()
{
    if (!m_objectManager) {
        qWarning() << "ObjectManager not initialized";
        return;
    }

    SceneObject* box = m_objectManager->createBox(QVector3D(2, 2, 2));
    qDebug() << "Box created via convenience method";
}

void Viewport3D::deleteSelected()
{
    if (!m_selectionManager || !m_objectManager) {
        qWarning() << "Selection or Object Manager not initialized";
        return;
    }

    QVector<SceneObject*> selected = m_selectionManager->selectedObjects();
    for (SceneObject* obj : selected) {
        m_objectManager->removeObject(obj);
    }
}

void Viewport3D::createTestCube()
{
    // Create test objects using the new object system

    // Create a floor using the old system (temporary)
    auto *floorEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *floorMesh = new Qt3DExtras::QCuboidMesh();
    floorMesh->setXExtent(10.0f);
    floorMesh->setYExtent(0.1f);
    floorMesh->setZExtent(10.0f);

    auto *floorMaterial = new Qt3DExtras::QPhongMaterial();
    floorMaterial->setDiffuse(QColor(140, 140, 140));
    floorMaterial->setAmbient(QColor(80, 80, 80));
    floorMaterial->setSpecular(QColor(200, 200, 200));
    floorMaterial->setShininess(20.0f);

    auto *floorTransform = new Qt3DCore::QTransform();
    floorTransform->setTranslation(QVector3D(0.0f, -0.05f, 0.0f));

    floorEntity->addComponent(floorMesh);
    floorEntity->addComponent(floorMaterial);
    floorEntity->addComponent(floorTransform);

    // Create test boxes using new object system
    SceneObject* box1 = m_objectManager->createBox(QVector3D(2, 2, 2));
    box1->setLocation(QVector3D(0, 1, 0));
    box1->setName("Cube");

    SceneObject* box2 = m_objectManager->createBox(QVector3D(1.5, 3, 1));
    box2->setLocation(QVector3D(3, 1.5, 0));
    box2->setName("Tall Box");

    qDebug() << "Test scene created with" << m_objectManager->objectCount() << "objects";
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

void Viewport3D::onObjectClicked(SceneObject* object)
{
    if (!object || !m_selectionManager) {
        return;
    }

    qDebug() << "Viewport received click on object:" << object->name();

    // TODO: Check for Shift modifier for multi-select
    // For now, single selection only
    m_selectionManager->selectObject(object, false);
}

void Viewport3D::onObjectAdded(SceneObject* object)
{
    if (!object) {
        return;
    }

    // Connect the object's clicked signal to our handler
    connect(object, &SceneObject::clicked, this, &Viewport3D::onObjectClicked);
    qDebug() << "Connected click handler for object:" << object->name();
}