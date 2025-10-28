#ifndef CUSTOM3DWINDOW_H
#define CUSTOM3DWINDOW_H

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QVector3D>

class Custom3DWindow : public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT

public:
    explicit Custom3DWindow(QScreen *screen = nullptr);
    ~Custom3DWindow();

    // Blender-style controls
    void setBlenderStyleNavigation(bool enabled) { m_blenderStyle = enabled; }
    void setFlyMode(bool enabled);
    bool flyMode() const { return m_flyMode; }

signals:
    void orbitRequested(int deltaX, int deltaY);
    void panRequested(int deltaX, int deltaY);
    void zoomRequested(float delta);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseLookRequested(int deltaX, int deltaY);
    void flyModeToggleRequested();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    bool m_blenderStyle;
    bool m_middlePressed;
    bool m_shiftPressed;
    QPoint m_lastMousePos;
    bool m_orbiting;
    bool m_panning;
    bool m_flyMode;  // Track if fly mode is active for mouse capture
};

#endif // CUSTOM3DWINDOW_H