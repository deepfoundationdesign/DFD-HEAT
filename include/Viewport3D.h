#ifndef VIEWPORT3D_H
#define VIEWPORT3D_H

#include <QWidget>
#include <Qt3DCore/QEntity>
#include <memory>

namespace Qt3DRender {
    class QCamera;
}

class Custom3DWindow;
class ViewportController;
class ViewportSettings;
class GridEntity;
class AxisEntity;

class Viewport3D : public QWidget
{
    Q_OBJECT

public:
    explicit Viewport3D(QWidget *parent = nullptr);
    ~Viewport3D();

    Qt3DCore::QEntity* rootEntity() const { return m_rootEntity; }
    Qt3DRender::QCamera* camera() const;
    ViewportController* controller() const { return m_controller.get(); }
    ViewportSettings* settings() const;

signals:
    void entitySelected(Qt3DCore::QEntity *entity);
    void faceSelected(int faceIndex);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onOrbitRequested(int deltaX, int deltaY);
    void onPanRequested(int deltaX, int deltaY);
    void onZoomRequested(float delta);

private:
    void setupScene();
    void createTestCube();
    void setupLighting();
    void setupGrid();
    void setupAxis();

    Custom3DWindow *m_view;
    Qt3DCore::QEntity *m_rootEntity;

    std::unique_ptr<ViewportController> m_controller;
    GridEntity *m_grid;
    AxisEntity *m_axis;
};

#endif // VIEWPORT3D_H