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
    , m_flyMode(false)
{
    // Enable mouse tracking to get move events even without buttons pressed
    setMouseGrabEnabled(true);

    // Set dark background color like Blender
    defaultFrameGraph()->setClearColor(QColor(60, 60, 60));
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

    // Fly mode mouse look (always active when in fly mode)
    if (m_flyMode) {
        QPoint delta = event->pos() - m_lastMousePos;
        emit mouseLookRequested(delta.x(), delta.y());
        m_lastMousePos = event->pos();
        event->accept();
        return;
    }

    // Orbit/Pan mode (middle mouse button)
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

void Custom3DWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "[Custom3DWindow::keyPressEvent] Key pressed:" << event->key()
             << "Text:" << event->text()
             << "IsAutoRepeat:" << event->isAutoRepeat()
             << "Qt::Key_QuoteLeft (numeric) =" << (int)Qt::Key_QuoteLeft;

    // Handle fly mode toggle keys
    // Qt::Key_QuoteLeft = 96 (backtick ` on US keyboards)
    // Key code 16781906 appears to be the ^ (caret) key on German keyboards
    if (!event->isAutoRepeat() &&
        (event->key() == Qt::Key_QuoteLeft || event->key() == 16781906)) {
        qDebug() << "[Custom3DWindow] Fly mode toggle key detected! Emitting flyModeToggleRequested()";
        emit flyModeToggleRequested();
        event->accept();
        return;
    }

    // Emit key press for other keys (movement keys handled by ViewportController)
    if (!event->isAutoRepeat()) {
        emit keyPressed(event->key());
    }

    // Let base class handle the event too
    Qt3DExtras::Qt3DWindow::keyPressEvent(event);
}

void Custom3DWindow::keyReleaseEvent(QKeyEvent *event)
{
    // Emit key release
    if (!event->isAutoRepeat()) {
        emit keyReleased(event->key());
    }

    // Let base class handle the event too
    Qt3DExtras::Qt3DWindow::keyReleaseEvent(event);
}