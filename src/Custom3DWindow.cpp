#include "Custom3DWindow.h"
#include <QDebug>
#include <QApplication>

Custom3DWindow::Custom3DWindow(QScreen *screen)
    : Qt3DExtras::Qt3DWindow(screen)
    , m_blenderStyle(true)
    , m_middlePressed(false)
    , m_shiftPressed(false)
    , m_orbiting(false)
    , m_panning(false)
{
    // Enable mouse tracking to get move events even without buttons pressed
    setMouseGrabEnabled(true);
}

Custom3DWindow::~Custom3DWindow() = default;

void Custom3DWindow::mousePressEvent(QMouseEvent *event)
{
    if (!m_blenderStyle) {
        Qt3DExtras::Qt3DWindow::mousePressEvent(event);
        return;
    }

    if (event->button() == Qt::MiddleButton) {
        m_middlePressed = true;
        m_lastMousePos = event->pos();
        m_shiftPressed = (event->modifiers() & Qt::ShiftModifier);

        if (m_shiftPressed) {
            m_panning = true;
            m_orbiting = false;
        } else {
            m_orbiting = true;
            m_panning = false;
        }

        event->accept();
        return;
    }

    // Let Qt3D handle other mouse buttons
    Qt3DExtras::Qt3DWindow::mousePressEvent(event);
}

void Custom3DWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_blenderStyle) {
        Qt3DExtras::Qt3DWindow::mouseMoveEvent(event);
        return;
    }

    if (m_middlePressed && (m_orbiting || m_panning)) {
        QPoint delta = event->pos() - m_lastMousePos;

        if (m_orbiting) {
            emit orbitRequested(delta.x(), delta.y());
        } else if (m_panning) {
            emit panRequested(delta.x(), delta.y());
        }

        m_lastMousePos = event->pos();
        event->accept();
        return;
    }

    // Let Qt3D handle other mouse movements
    Qt3DExtras::Qt3DWindow::mouseMoveEvent(event);
}

void Custom3DWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_blenderStyle) {
        Qt3DExtras::Qt3DWindow::mouseReleaseEvent(event);
        return;
    }

    if (event->button() == Qt::MiddleButton) {
        m_middlePressed = false;
        m_orbiting = false;
        m_panning = false;
        m_shiftPressed = false;
        event->accept();
        return;
    }

    // Let Qt3D handle other mouse button releases
    Qt3DExtras::Qt3DWindow::mouseReleaseEvent(event);
}

void Custom3DWindow::wheelEvent(QWheelEvent *event)
{
    if (!m_blenderStyle) {
        Qt3DExtras::Qt3DWindow::wheelEvent(event);
        return;
    }

    float delta = event->angleDelta().y() / 120.0f;
    emit zoomRequested(delta);
    event->accept();
}