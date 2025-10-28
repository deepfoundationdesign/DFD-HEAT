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
class ModeManager;
class ObjectManager;
class SelectionManager;
class SceneObject;
class CrosshairsOverlay;
class CrosshairsEntity3D;

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

    // Object system access
    ModeManager* modeManager() const { return m_modeManager.get(); }
    ObjectManager* objectManager() const { return m_objectManager.get(); }
    SelectionManager* selectionManager() const { return m_selectionManager.get(); }

    // Convenience methods
    void createBox();
    void deleteSelected();

signals:
    void entitySelected(Qt3DCore::QEntity *entity);
    void faceSelected(int faceIndex);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onOrbitRequested(int deltaX, int deltaY);
    void onPanRequested(int deltaX, int deltaY);
    void onZoomRequested(float delta);
    void onObjectClicked(SceneObject* object);
    void onObjectAdded(SceneObject* object);
    void onFlyModeToggled(bool active);

private:
    void setupScene();
    void setupObjectSystem();
    void createTestCube();
    void setupLighting();
    void setupGrid();
    void setupAxis();
    void setupCrosshairs();

    Custom3DWindow *m_view;
    Qt3DCore::QEntity *m_rootEntity;

    std::unique_ptr<ViewportController> m_controller;
    std::unique_ptr<ModeManager> m_modeManager;
    std::unique_ptr<ObjectManager> m_objectManager;
    std::unique_ptr<SelectionManager> m_selectionManager;

    GridEntity *m_grid;
    AxisEntity *m_axis;
    CrosshairsOverlay *m_crosshairs;  // Old widget-based (doesn't work with createWindowContainer)
    CrosshairsEntity3D *m_crosshairs3D;  // New Qt3D-based crosshairs
};

#endif // VIEWPORT3D_H