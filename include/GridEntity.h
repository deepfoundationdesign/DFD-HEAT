#ifndef GRIDENTITY_H
#define GRIDENTITY_H

#include <Qt3DCore/QEntity>
#include <QColor>
#include <memory>

namespace Qt3DRender {
    class QGeometryRenderer;
    class QMaterial;
}

class GridEntity : public Qt3DCore::QEntity
{
    Q_OBJECT

public:
    explicit GridEntity(Qt3DCore::QNode *parent = nullptr);
    ~GridEntity();

    void setGridSize(float size);
    void setGridDivisions(int divisions);
    void setColor(const QColor &color);
    void setVisible(bool visible);

private:
    void createGrid();

    Qt3DRender::QGeometryRenderer *m_mesh;
    Qt3DRender::QMaterial *m_material;

    float m_gridSize;
    int m_gridDivisions;
    QColor m_color;
};

#endif // GRIDENTITY_H