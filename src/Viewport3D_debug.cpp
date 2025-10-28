#include "viewport/Viewport3D.h"
#include "viewport/ViewportController.h"
#include "viewport/ViewportSettings.h"

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCuboidMesh>

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
    container->setMouseTracking(true);
    container->setFocusPolicy(Qt::StrongFocus);

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
    // Debug: Print event types to see what we're receiving
    if (event->type() == QEvent::MouseButtonPress ||
        event->type() == QEvent::MouseButtonRelease ||
        event->type() == QEvent::MouseMove ||
        event->type() == QEvent::Wheel) {

        // Forward events to our controller
        bool handled = m_controller->eventFilter(obj, event);
        if (handled) {
            return true;
        }
    }

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

    // Setup scene elements
    setupLighting();
    createTestCube();

    // Skip grid and axis for now to avoid crash
    // setupGrid();
    // setupAxis();
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
}