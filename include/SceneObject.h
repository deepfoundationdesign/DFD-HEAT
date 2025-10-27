#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <QVector3D>
#include <QUuid>
#include <QString>

class MeshData;

namespace Qt3DRender {
    class QMaterial;
    class QGeometryRenderer;
}

/**
 * @brief Base class for all scene objects
 *
 * SceneObject provides transform properties (location, rotation, scale),
 * object properties (name, UUID, visibility), and mesh data access for
 * both Object Mode and Edit Mode operations.
 */
class SceneObject : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QVector3D location READ location WRITE setLocation NOTIFY transformChanged)
    Q_PROPERTY(QVector3D rotation READ rotation WRITE setRotation NOTIFY transformChanged)
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY transformChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY propertiesChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY propertiesChanged)
    Q_PROPERTY(bool locked READ isLocked WRITE setLocked NOTIFY propertiesChanged)

public:
    explicit SceneObject(Qt3DCore::QNode *parent = nullptr);
    virtual ~SceneObject();

    // Transform properties (world space)
    QVector3D location() const;
    QVector3D rotation() const;  // Euler angles in degrees
    QVector3D scale() const;
    QVector3D dimensions() const;  // Actual dimensions in meters

    void setLocation(const QVector3D& pos);
    void setRotation(const QVector3D& rot);
    void setScale(const QVector3D& scale);
    virtual void setDimensions(const QVector3D& dim);

    // Object properties
    QString name() const { return m_name; }
    QUuid uuid() const { return m_uuid; }
    bool isVisible() const { return m_visible; }
    bool isLocked() const { return m_locked; }
    int materialId() const { return m_materialId; }

    void setName(const QString& name);
    void setVisible(bool visible);
    void setLocked(bool locked);
    void setMaterialId(int id);

    // Mesh access for edit mode
    MeshData* meshData() { return m_meshData; }
    const MeshData* meshData() const { return m_meshData; }

    // Geometry update (call after modifying mesh data)
    virtual void updateGeometry();

    // Selection state (managed by SelectionManager)
    bool isSelected() const { return m_selected; }
    void setSelected(bool selected);

signals:
    void transformChanged();
    void propertiesChanged();
    void selectionChanged(bool selected);

protected:
    // Components (for derived classes to set up)
    Qt3DCore::QTransform* m_transform;
    Qt3DRender::QMaterial* m_material;
    Qt3DRender::QGeometryRenderer* m_renderer;

    // Mesh data
    MeshData* m_meshData;

    // Derived classes implement mesh generation
    virtual void generateMesh() = 0;

private:
    // Transform
    QVector3D m_dimensions;

    // Properties
    QString m_name;
    QUuid m_uuid;
    bool m_visible;
    bool m_locked;
    int m_materialId;
    bool m_selected;

    // Counter for default naming
    static int s_objectCounter;
};

#endif // SCENEOBJECT_H
