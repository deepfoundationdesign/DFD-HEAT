#include "ViewportController.h"
#include "ViewportSettings.h"

#include <Qt3DRender/QCamera>
#include <Qt3DInput/QMouseDevice>
#include <Qt3DInput/QKeyboardDevice>
#include <Qt3DInput/QMouseHandler>
#include <Qt3DInput/QKeyboardHandler>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtMath>
#include <QDebug>

ViewportController::ViewportController(Qt3DRender::QCamera *camera, QObject *parent)
    : QObject(parent)
    , m_camera(camera)
    , m_settings(std::make_unique<ViewportSettings>())
    , m_navigationMode(Orbit)
    , m_orbitSpeed(0.5f)
    , m_panSpeed(0.01f)
    , m_zoomSpeed(0.1f)
    , m_radius(17.3205f)  // sqrt(10^2 + 10^2 + 10^2) for position (10, 10, 10)
    , m_azimuth(45.0f)    // Equal X and Z components
    , m_elevation(35.264f) // arcsin(10/17.3205) for Y=10
    , m_target(0, 0, 0)
    , m_mousePressed(false)
    , m_middleMousePressed(false)
    , m_activeButton(Qt::NoButton)
    , m_flyModeActive(false)
    , m_flySpeed(5.0f)  // 5 units per second
    , m_flyMouseSensitivity(0.15f)
    , m_yaw(45.0f)
    , m_pitch(35.264f)
    , m_flyPosition(10, 10, 10)
{
    // Setup fly mode timer for continuous movement
    m_flyModeTimer = new QTimer(this);
    m_flyModeTimer->setInterval(16);  // ~60 FPS
    connect(m_flyModeTimer, &QTimer::timeout, this, &ViewportController::updateFlyCamera);

    if (m_camera) {
        updateCameraPosition();
    }
}

ViewportController::~ViewportController() = default;

void ViewportController::setCamera(Qt3DRender::QCamera *camera)
{
    m_camera = camera;
    updateCameraPosition();
}

void ViewportController::setNavigationMode(NavigationMode mode)
{
    if (m_navigationMode != mode) {
        m_navigationMode = mode;
        emit navigationModeChanged(mode);
    }
}

void ViewportController::startOrbit(const QPoint &pos)
{
    m_lastMousePos = pos;
    m_mousePressed = true;
}

void ViewportController::orbit(const QPoint &pos)
{
    if (!m_mousePressed || !m_camera) return;

    QPoint delta = pos - m_lastMousePos;

    // Blender-style orbit (horizontal and vertical)
    m_azimuth -= delta.x() * m_orbitSpeed * m_settings->orbitSensitivity();
    m_elevation += delta.y() * m_orbitSpeed * m_settings->orbitSensitivity();

    // Clamp elevation to avoid flipping
    m_elevation = qBound(-89.0f, m_elevation, 89.0f);

    updateCameraPosition();
    m_lastMousePos = pos;
}

void ViewportController::startPan(const QPoint &pos)
{
    m_lastMousePos = pos;
    m_middleMousePressed = true;
}

void ViewportController::pan(const QPoint &pos)
{
    if (!m_middleMousePressed || !m_camera) return;

    QPoint delta = pos - m_lastMousePos;

    // Apply pan deltas (X inverted, Y normal for natural panning)
    float deltaX = -delta.x() * m_panSpeed * m_settings->panSensitivity();
    float deltaY = delta.y() * m_panSpeed * m_settings->panSensitivity();

    if (m_settings->invertPanX()) deltaX = -deltaX;
    if (m_settings->invertPanY()) deltaY = -deltaY;

    // Calculate right and up vectors relative to camera
    QVector3D forward = (m_target - m_camera->position()).normalized();
    QVector3D right = QVector3D::crossProduct(forward, m_camera->upVector()).normalized();
    QVector3D up = QVector3D::crossProduct(right, forward).normalized();

    // Pan the target point (reduced radius factor for better control)
    m_target += right * deltaX * m_radius * 0.1f;
    m_target += up * deltaY * m_radius * 0.1f;

    updateCameraPosition();
    m_lastMousePos = pos;
}

void ViewportController::zoom(float delta)
{
    if (!m_camera) return;

    // Blender-style zoom (scroll up = zoom in, scroll down = zoom out)
    float zoomFactor = 1.0f - (delta * m_zoomSpeed * m_settings->zoomSensitivity());
    m_radius *= zoomFactor;
    m_radius = qBound(0.1f, m_radius, 1000.0f);

    updateCameraPosition();
}

void ViewportController::focusOnPoint(const QVector3D &point)
{
    m_target = point;
    updateCameraPosition();
}

void ViewportController::frameAll()
{
    // TODO: Calculate bounding box of all objects and fit camera
    m_radius = 10.0f;
    m_target = QVector3D(0, 0, 0);
    updateCameraPosition();
}

void ViewportController::viewFront()
{
    m_azimuth = 0.0f;
    m_elevation = 0.0f;
    updateCameraPosition();
}

void ViewportController::viewRight()
{
    m_azimuth = 90.0f;
    m_elevation = 0.0f;
    updateCameraPosition();
}

void ViewportController::viewTop()
{
    m_azimuth = 0.0f;
    m_elevation = 89.9f;  // Not exactly 90 to avoid gimbal lock
    updateCameraPosition();
}

void ViewportController::viewBack()
{
    m_azimuth = 180.0f;
    m_elevation = 0.0f;
    updateCameraPosition();
}

void ViewportController::viewLeft()
{
    m_azimuth = -90.0f;
    m_elevation = 0.0f;
    updateCameraPosition();
}

void ViewportController::viewBottom()
{
    m_azimuth = 0.0f;
    m_elevation = -89.9f;
    updateCameraPosition();
}

void ViewportController::updateCameraPosition()
{
    if (!m_camera) return;

    // Convert spherical to Cartesian coordinates
    float azimuthRad = qDegreesToRadians(m_azimuth);
    float elevationRad = qDegreesToRadians(m_elevation);

    float x = m_radius * qCos(elevationRad) * qSin(azimuthRad);
    float y = m_radius * qSin(elevationRad);
    float z = m_radius * qCos(elevationRad) * qCos(azimuthRad);

    QVector3D cameraPos = m_target + QVector3D(x, y, z);

    m_camera->setPosition(cameraPos);
    m_camera->setViewCenter(m_target);

    // Keep up vector consistent (Y-up like Blender)
    m_camera->setUpVector(QVector3D(0, 1, 0));

    emit cameraChanged();
}

bool ViewportController::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress: {
        auto *e = static_cast<QMouseEvent*>(event);
        if (e->button() == Qt::MiddleButton) {
            if (e->modifiers() & Qt::ShiftModifier) {
                startPan(e->position().toPoint());
            } else {
                startOrbit(e->position().toPoint());
            }
            return true;
        }
        break;
    }
    case QEvent::MouseButtonRelease: {
        auto *e = static_cast<QMouseEvent*>(event);
        if (e->button() == Qt::MiddleButton) {
            m_mousePressed = false;
            m_middleMousePressed = false;
            return true;
        }
        break;
    }
    case QEvent::MouseMove: {
        auto *e = static_cast<QMouseEvent*>(event);
        if (m_middleMousePressed) {
            pan(e->position().toPoint());
            return true;
        } else if (m_mousePressed) {
            orbit(e->position().toPoint());
            return true;
        }
        break;
    }
    case QEvent::Wheel: {
        auto *e = static_cast<QWheelEvent*>(event);
        zoom(e->angleDelta().y() / 120.0f);
        return true;
    }
    default:
        break;
    }

    return QObject::eventFilter(obj, event);
}

QVector3D ViewportController::screenToWorld(const QPoint &screenPos)
{
    // TODO: Implement screen to world coordinate conversion
    return QVector3D();
}

void ViewportController::toggleFlyMode()
{
    qDebug() << "[ViewportController::toggleFlyMode] Called! Current state:" << m_flyModeActive;

    m_flyModeActive = !m_flyModeActive;

    qDebug() << "[ViewportController::toggleFlyMode] New state:" << m_flyModeActive;

    if (m_flyModeActive) {
        qDebug() << "  FLY MODE ACTIVATED";

        // Initialize fly mode from current camera position
        m_flyPosition = m_camera->position();

        // Calculate initial yaw and pitch from current camera orientation
        QVector3D forward = (m_camera->viewCenter() - m_camera->position()).normalized();
        m_yaw = qRadiansToDegrees(qAtan2(forward.x(), forward.z()));
        m_pitch = qRadiansToDegrees(qAsin(-forward.y()));

        qDebug() << "  Initial position:" << m_flyPosition;
        qDebug() << "  Initial yaw:" << m_yaw << "pitch:" << m_pitch;

        // Start the update timer
        m_flyModeTimer->start();

    } else {
        qDebug() << "  FLY MODE DEACTIVATED";

        // Stop the update timer
        m_flyModeTimer->stop();

        // Clear pressed keys
        m_pressedKeys.clear();

        // Return to orbit mode - recalculate spherical coordinates from current position
        QVector3D pos = m_camera->position();
        QVector3D target = m_camera->viewCenter();

        m_target = target;
        QVector3D offset = pos - target;
        m_radius = offset.length();

        if (m_radius > 0.001f) {
            m_azimuth = qRadiansToDegrees(qAtan2(offset.x(), offset.z()));
            m_elevation = qRadiansToDegrees(qAsin(offset.y() / m_radius));
        }

        qDebug() << "  Returned to orbit mode";
    }

    emit flyModeToggled(m_flyModeActive);
    qDebug() << "  flyModeToggled signal emitted with value:" << m_flyModeActive;
}

void ViewportController::handleKeyPress(int key)
{
    if (!m_flyModeActive) return;

    m_pressedKeys.insert(key);
}

void ViewportController::handleKeyRelease(int key)
{
    if (!m_flyModeActive) return;

    m_pressedKeys.remove(key);
}

void ViewportController::handleMouseLook(int deltaX, int deltaY)
{
    if (!m_flyModeActive || !m_camera) return;

    // Update yaw (horizontal) and pitch (vertical)
    m_yaw -= deltaX * m_flyMouseSensitivity;
    m_pitch += deltaY * m_flyMouseSensitivity;

    // Clamp pitch to prevent camera flipping
    m_pitch = qBound(-89.0f, m_pitch, 89.0f);

    // Normalize yaw to 0-360 range
    while (m_yaw < 0.0f) m_yaw += 360.0f;
    while (m_yaw >= 360.0f) m_yaw -= 360.0f;
}

void ViewportController::updateFlyCamera()
{
    if (!m_flyModeActive || !m_camera) return;

    // Calculate movement delta based on time
    float deltaTime = m_flyModeTimer->interval() / 1000.0f;  // Convert ms to seconds
    float moveAmount = m_flySpeed * deltaTime;

    // Calculate camera direction vectors
    float yawRad = qDegreesToRadians(m_yaw);
    float pitchRad = qDegreesToRadians(m_pitch);

    // Forward vector (direction camera is looking)
    QVector3D forward(
        qSin(yawRad) * qCos(pitchRad),
        -qSin(pitchRad),
        qCos(yawRad) * qCos(pitchRad)
    );
    forward.normalize();

    // Right vector (perpendicular to forward, for strafing)
    QVector3D right = QVector3D::crossProduct(forward, QVector3D(0, 1, 0)).normalized();

    // World up vector (for Q/E)
    QVector3D worldUp(0, 1, 0);

    // Process movement based on pressed keys
    if (m_pressedKeys.contains(Qt::Key_W)) {
        m_flyPosition += forward * moveAmount;
    }
    if (m_pressedKeys.contains(Qt::Key_S)) {
        m_flyPosition -= forward * moveAmount;
    }
    if (m_pressedKeys.contains(Qt::Key_A)) {
        m_flyPosition -= right * moveAmount;
    }
    if (m_pressedKeys.contains(Qt::Key_D)) {
        m_flyPosition += right * moveAmount;
    }
    if (m_pressedKeys.contains(Qt::Key_E)) {
        m_flyPosition += worldUp * moveAmount;  // Up along world Y-axis
    }
    if (m_pressedKeys.contains(Qt::Key_Q)) {
        m_flyPosition -= worldUp * moveAmount;  // Down along world Y-axis
    }

    // Update camera position
    m_camera->setPosition(m_flyPosition);

    // Update camera view center (where it's looking)
    QVector3D viewCenter = m_flyPosition + forward;
    m_camera->setViewCenter(viewCenter);

    // Keep up vector as world up
    m_camera->setUpVector(QVector3D(0, 1, 0));

    emit cameraChanged();
}