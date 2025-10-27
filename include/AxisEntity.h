#ifndef AXISENTITY_H
#define AXISENTITY_H

#include <Qt3DCore/QEntity>

namespace Qt3DCore {
    class QTransform;
}

namespace Qt3DExtras {
    class QCylinderMesh;
    class QConeMesh;
    class QPhongMaterial;
}

class AxisEntity : public Qt3DCore::QEntity
{
    Q_OBJECT

public:
    explicit AxisEntity(Qt3DCore::QNode *parent = nullptr);
    ~AxisEntity();

    void setLength(float length);
    void setThickness(float thickness);
    void setVisible(bool visible);

private:
    void createAxis();
    Qt3DCore::QEntity* createAxisLine(const QVector3D &direction, const QColor &color);

    float m_length;
    float m_thickness;

    Qt3DCore::QEntity *m_xAxis;
    Qt3DCore::QEntity *m_yAxis;
    Qt3DCore::QEntity *m_zAxis;
};

#endif // AXISENTITY_H