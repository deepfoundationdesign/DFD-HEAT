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
{
    qDebug() << "[ViewportController] Initialized with spherical coords for camera at (10, 10, 10):";
    qDebug() << "  radius=" << m_radius << "azimuth=" << m_azimuth << "° elevation=" << m_elevation << "°";

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
    qDebug() << "[ViewportController::orbit] pos=" << pos << "lastPos=" << m_lastMousePos << "delta=" << delta;

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
    qDebug() << "[ViewportController::pan] pos=" << pos << "lastPos=" << m_lastMousePos << "delta=" << delta;

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

    qDebug() << "[ViewportController::zoom] delta=" << delta;
    qDebug() << "  Old radius:" << m_radius;

    // Blender-style zoom (scroll up = zoom in, scroll down = zoom out)
    float zoomFactor = 1.0f - (delta * m_zoomSpeed * m_settings->zoomSensitivity());
    m_radius *= zoomFactor;
    m_radius = qBound(0.1f, m_radius, 1000.0f);

    qDebug() << "  New radius:" << m_radius << "(zoom factor:" << zoomFactor << ")";

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

    // DEBUG: Log camera state before update
    QVector3D oldPos = m_camera->position();
    qDebug() << "[ViewportController] updateCameraPosition() called";
    qDebug() << "  Current camera position:" << oldPos;
    qDebug() << "  Spherical coords: radius=" << m_radius
             << "azimuth=" << m_azimuth << "° elevation=" << m_elevation << "°";

    // Convert spherical to Cartesian coordinates
    float azimuthRad = qDegreesToRadians(m_azimuth);
    float elevationRad = qDegreesToRadians(m_elevation);

    float x = m_radius * qCos(elevationRad) * qSin(azimuthRad);
    float y = m_radius * qSin(elevationRad);
    float z = m_radius * qCos(elevationRad) * qCos(azimuthRad);

    QVector3D cameraPos = m_target + QVector3D(x, y, z);

    // DEBUG: Log new position and delta
    QVector3D delta = cameraPos - oldPos;
    qDebug() << "  Calculated new position:" << cameraPos;
    qDebug() << "  Delta (movement):" << delta;
    qDebug() << "  Delta magnitude:" << delta.length();

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