#include "viewport/Viewport3D.h"
#include "viewport/ViewportController.h"
#include "viewport/ViewportSettings.h"
#include "entities/GridEntity.h"
#include "entities/AxisEntity.h"

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DRender/QDirectionalLight>

#include <QVBoxLayout>
#include <QWidget>

Viewport3D::Viewport3D(QWidget *parent)
    : QWidget(parent)
    , m_view(new Qt3DExtras::Qt3DWindow())
    , m_rootEntity(new Qt3DCore::QEntity())
    , m_controller(std::make_unique<ViewportController>(m_view->camera()))
    , m_grid(nullptr)
    , m_axis(nullptr)
{
    // Create container widget for Qt3D window
    QWidget *container = QWidget::createWindowContainer(m_view);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(container);

    m_view->setRootEntity(m_rootEntity);

    // Install event filter for mouse/keyboard input
    container->installEventFilter(this);

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
    // Forward events to our controller
    return m_controller->eventFilter(obj, event);
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

    // Set background color (removed - requires different approach)

    // Setup scene elements
    setupLighting();
    setupGrid();
    setupAxis();
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

    // Ambient fill light
    auto *fillLightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *fillLight = new Qt3DRender::QDirectionalLight(fillLightEntity);
    fillLight->setColor(QColor(100, 100, 100));
    fillLight->setIntensity(0.3f);
    fillLight->setWorldDirection(QVector3D(1, 0.5f, 0.5f).normalized());
    fillLightEntity->addComponent(fillLight);
}

void Viewport3D::setupGrid()
{
    ViewportSettings *settings = m_controller->settings();
    m_grid = new GridEntity(m_rootEntity);
    m_grid->setGridSize(settings->gridSize());
    m_grid->setGridDivisions(settings->gridDivisions());
    m_grid->setColor(settings->gridColor());
    m_grid->setVisible(settings->showGrid());

    // Connect settings changes
    connect(settings, &ViewportSettings::showGridChanged, [this]() {
        m_grid->setVisible(this->settings()->showGrid());
    });
    connect(settings, &ViewportSettings::gridSizeChanged, [this]() {
        m_grid->setGridSize(this->settings()->gridSize());
    });
    connect(settings, &ViewportSettings::gridDivisionsChanged, [this]() {
        m_grid->setGridDivisions(this->settings()->gridDivisions());
    });
}

void Viewport3D::setupAxis()
{
    ViewportSettings *settings = m_controller->settings();
    m_axis = new AxisEntity(m_rootEntity);
    m_axis->setLength(settings->axisLength());
    m_axis->setThickness(settings->axisThickness());
    m_axis->setVisible(settings->showAxis());

    // Connect settings changes
    connect(settings, &ViewportSettings::showAxisChanged, [this]() {
        m_axis->setVisible(this->settings()->showAxis());
    });
    connect(settings, &ViewportSettings::axisLengthChanged, [this]() {
        m_axis->setLength(this->settings()->axisLength());
    });
}

void Viewport3D::createTestCube()
{
    // Create a test wall element
    auto *wallEntity = new Qt3DCore::QEntity(m_rootEntity);

    // Wall mesh (thin cuboid)
    auto *wallMesh = new Qt3DExtras::QCuboidMesh();
    wallMesh->setXExtent(4.0f);
    wallMesh->setYExtent(3.0f);
    wallMesh->setZExtent(0.2f);

    // Wall material
    auto *wallMaterial = new Qt3DExtras::QPhongMaterial();
    wallMaterial->setDiffuse(QColor(180, 180, 180));
    wallMaterial->setAmbient(QColor(100, 100, 100));
    wallMaterial->setSpecular(QColor(50, 50, 50));
    wallMaterial->setShininess(10.0f);

    // Wall transform
    auto *wallTransform = new Qt3DCore::QTransform();
    wallTransform->setTranslation(QVector3D(0.0f, 1.5f, 0.0f));

    wallEntity->addComponent(wallMesh);
    wallEntity->addComponent(wallMaterial);
    wallEntity->addComponent(wallTransform);

    // Create floor
    auto *floorEntity = new Qt3DCore::QEntity(m_rootEntity);

    auto *floorMesh = new Qt3DExtras::QCuboidMesh();
    floorMesh->setXExtent(8.0f);
    floorMesh->setYExtent(0.1f);
    floorMesh->setZExtent(8.0f);

    auto *floorMaterial = new Qt3DExtras::QPhongMaterial();
    floorMaterial->setDiffuse(QColor(120, 120, 120));

    auto *floorTransform = new Qt3DCore::QTransform();
    floorTransform->setTranslation(QVector3D(0.0f, -0.05f, 0.0f));

    floorEntity->addComponent(floorMesh);
    floorEntity->addComponent(floorMaterial);
    floorEntity->addComponent(floorTransform);
}