#ifndef VIEWPORTCONTROLLER_H
#define VIEWPORTCONTROLLER_H

#include <QObject>
#include <QVector3D>
#include <QPoint>
#include <QSet>
#include <QTimer>
#include <memory>

namespace Qt3DRender {
    class QCamera;
}

namespace Qt3DInput {
    class QMouseDevice;
    class QKeyboardDevice;
    class QMouseHandler;
    class QKeyboardHandler;
}

class ViewportSettings;

class ViewportController : public QObject
{
    Q_OBJECT

public:
    enum NavigationMode {
        Orbit,
        Pan,
        Zoom,
        Fly
    };

    explicit ViewportController(Qt3DRender::QCamera *camera, QObject *parent = nullptr);
    ~ViewportController();

    void setCamera(Qt3DRender::QCamera *camera);
    void setNavigationMode(NavigationMode mode);
    NavigationMode navigationMode() const { return m_navigationMode; }

    // Blender-style navigation
    void startOrbit(const QPoint &pos);
    void orbit(const QPoint &pos);
    void startPan(const QPoint &pos);
    void pan(const QPoint &pos);
    void zoom(float delta);
    void focusOnPoint(const QVector3D &point);
    void frameAll();

    // Camera presets (numpad views like Blender)
    void viewFront();  // Numpad 1
    void viewRight();  // Numpad 3
    void viewTop();    // Numpad 7
    void viewBack();   // Ctrl+Numpad 1
    void viewLeft();   // Ctrl+Numpad 3
    void viewBottom(); // Ctrl+Numpad 7

    ViewportSettings* settings() const { return m_settings.get(); }

    // Fly mode controls
    void toggleFlyMode();
    bool isFlyModeActive() const { return m_flyModeActive; }
    void handleKeyPress(int key);
    void handleKeyRelease(int key);
    void handleMouseLook(int deltaX, int deltaY);

signals:
    void navigationModeChanged(NavigationMode mode);
    void cameraChanged();
    void flyModeToggled(bool active);

public:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void updateCameraPosition();
    void updateFlyCamera();  // Update camera for fly mode
    void updateFlyCameraOrientation();  // Update camera orientation immediately (for mouse look)
    QVector3D screenToWorld(const QPoint &screenPos);

    Qt3DRender::QCamera *m_camera;
    std::unique_ptr<ViewportSettings> m_settings;

    NavigationMode m_navigationMode;

    // Orbit controls
    QPoint m_lastMousePos;
    float m_orbitSpeed;
    float m_panSpeed;
    float m_zoomSpeed;

    // Camera spherical coordinates
    float m_radius;
    float m_azimuth;  // Horizontal angle
    float m_elevation; // Vertical angle
    QVector3D m_target; // Look-at point

    bool m_mousePressed;
    bool m_middleMousePressed;
    Qt::MouseButton m_activeButton;

    // Fly mode state
    bool m_flyModeActive;
    QSet<int> m_pressedKeys;  // Track currently pressed keys
    QTimer *m_flyModeTimer;   // Timer for continuous movement
    float m_flySpeed;         // Movement speed in units/second
    float m_flyMouseSensitivity; // Mouse look sensitivity

    // Fly mode camera orientation (first-person)
    float m_yaw;   // Horizontal rotation (around Y axis)
    float m_pitch; // Vertical rotation (look up/down)
    QVector3D m_flyPosition; // Direct camera position in fly mode
};

#endif // VIEWPORTCONTROLLER_H