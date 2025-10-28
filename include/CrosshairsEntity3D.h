#ifndef CROSSHAIRSENTITY3D_H
#define CROSSHAIRSENTITY3D_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QGeometry>
#include <Qt3DExtras/QPhongMaterial>

namespace Qt3DCore {
    class QTransform;
    class QBuffer;
    class QAttribute;
}

namespace Qt3DRender {
    class QGeometryRenderer;
    class QLayer;
}

// Qt3D entity that renders crosshairs in screen space using orthographic projection
class CrosshairsEntity3D : public Qt3DCore::QEntity
{
    Q_OBJECT

public:
    explicit CrosshairsEntity3D(Qt3DCore::QNode *parent = nullptr);

    void setLayer(Qt3DRender::QLayer* layer);
    void setVisible(bool visible);

private:
    void createCrosshairsGeometry();

    Qt3DCore::QGeometry* m_geometry;
    Qt3DRender::QGeometryRenderer* m_renderer;
    Qt3DExtras::QPhongMaterial* m_material;
    Qt3DCore::QTransform* m_transform;

    float m_crosshairSize;  // Half-length of crosshair lines
    float m_gap;            // Gap in the center
};

#endif // CROSSHAIRSENTITY3D_H
