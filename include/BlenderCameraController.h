#ifndef BLENDERCAMERACONTROLLER_H
#define BLENDERCAMERACONTROLLER_H

#include <Qt3DCore/QEntity>
#include <Qt3DInput/QMouseDevice>
#include <Qt3DInput/QKeyboardDevice>

namespace Qt3DRender {
    class QCamera;
}

namespace Qt3DInput {
    class QMouseHandler;
    class QKeyboardHandler;
}

class BlenderCameraController : public Qt3DCore::QEntity
{
    Q_OBJECT

public:
    explicit BlenderCameraController(Qt3DCore::QNode *parent = nullptr);
    ~BlenderCameraController();

    Qt3DRender::QCamera *camera() const;
    void setCamera(Qt3DRender::QCamera *camera);

    float linearSpeed() const;
    void setLinearSpeed(float speed);

    float lookSpeed() const;
    void setLookSpeed(float speed);

private slots:
    void onMousePressed();
    void onMouseReleased();
    void onMousePositionChanged(float dx, float dy);
    void onWheelEvent(float deltaY);

private:
    void orbit(float dx, float dy);
    void pan(float dx, float dy);
    void zoom(float delta);

    Qt3DRender::QCamera *m_camera;
    Qt3DInput::QMouseDevice *m_mouseDevice;
    Qt3DInput::QKeyboardDevice *m_keyboardDevice;
    Qt3DInput::QMouseHandler *m_mouseHandler;
    Qt3DInput::QKeyboardHandler *m_keyboardHandler;

    float m_linearSpeed;
    float m_lookSpeed;

    bool m_leftMousePressed;
    bool m_middleMousePressed;
    bool m_rightMousePressed;
    bool m_shiftPressed;

    QPointF m_lastMousePosition;
    QVector3D m_cameraTarget;
    float m_distance;
};

#endif // BLENDERCAMERACONTROLLER_H