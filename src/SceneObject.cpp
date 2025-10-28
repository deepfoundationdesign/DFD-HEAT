#include "SceneObject.h"
#include "MeshData.h"
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QPickEvent>
#include <Qt3DExtras/QPhongMaterial>
#include <QDebug>

int SceneObject::s_objectCounter = 0;

SceneObject::SceneObject(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , m_transform(new Qt3DCore::QTransform(this))
    , m_material(nullptr)
    , m_renderer(nullptr)
    , m_picker(new Qt3DRender::QObjectPicker(this))
    , m_meshData(new MeshData())
    , m_dimensions(1.0f, 1.0f, 1.0f)
    , m_name(QString("Object_%1").arg(++s_objectCounter))
    , m_uuid(QUuid::createUuid())
    , m_visible(true)
    , m_locked(false)
    , m_materialId(-1)
    , m_selected(false)
{
    // Add transform component
    addComponent(m_transform);

    // Setup object picker for mouse selection
    m_picker->setEnabled(true);
    m_picker->setHoverEnabled(false);  // We only care about clicks, not hover
    addComponent(m_picker);

    // Connect picker signal to our slot (only respond to left mouse button)
    connect(m_picker, &Qt3DRender::QObjectPicker::clicked, this, [this](Qt3DRender::QPickEvent* event) {
        // Only select on left mouse button (not middle or right)
        if (event && event->button() == Qt3DRender::QPickEvent::LeftButton) {
            this->onObjectClicked();
        }
    });

    qDebug() << "SceneObject created:" << m_name << "UUID:" << m_uuid.toString();
}

SceneObject::~SceneObject()
{
    delete m_meshData;
    qDebug() << "SceneObject destroyed:" << m_name;
}

QVector3D SceneObject::location() const
{
    return m_transform->translation();
}

QVector3D SceneObject::rotation() const
{
    // Convert quaternion to Euler angles (in degrees)
    QQuaternion q = m_transform->rotation();

    // Calculate Euler angles (XYZ order)
    float x, y, z;

    // Roll (x-axis rotation)
    float sinr_cosp = 2 * (q.scalar() * q.x() + q.y() * q.z());
    float cosr_cosp = 1 - 2 * (q.x() * q.x() + q.y() * q.y());
    x = std::atan2(sinr_cosp, cosr_cosp);

    // Pitch (y-axis rotation)
    float sinp = 2 * (q.scalar() * q.y() - q.z() * q.x());
    if (std::abs(sinp) >= 1)
        y = std::copysign(M_PI / 2, sinp); // Use 90 degrees if out of range
    else
        y = std::asin(sinp);

    // Yaw (z-axis rotation)
    float siny_cosp = 2 * (q.scalar() * q.z() + q.x() * q.y());
    float cosy_cosp = 1 - 2 * (q.y() * q.y() + q.z() * q.z());
    z = std::atan2(siny_cosp, cosy_cosp);

    // Convert radians to degrees
    return QVector3D(qRadiansToDegrees(x), qRadiansToDegrees(y), qRadiansToDegrees(z));
}

QVector3D SceneObject::scale() const
{
    return m_transform->scale3D();
}

QVector3D SceneObject::dimensions() const
{
    return m_dimensions;
}

void SceneObject::setLocation(const QVector3D& pos)
{
    if (m_locked) {
        qWarning() << "Cannot modify locked object:" << m_name;
        return;
    }

    m_transform->setTranslation(pos);
    emit transformChanged();
}

void SceneObject::setRotation(const QVector3D& rot)
{
    if (m_locked) {
        qWarning() << "Cannot modify locked object:" << m_name;
        return;
    }

    // Convert Euler angles (degrees) to quaternion
    QQuaternion qx = QQuaternion::fromAxisAndAngle(1, 0, 0, rot.x());
    QQuaternion qy = QQuaternion::fromAxisAndAngle(0, 1, 0, rot.y());
    QQuaternion qz = QQuaternion::fromAxisAndAngle(0, 0, 1, rot.z());

    m_transform->setRotation(qz * qy * qx);
    emit transformChanged();
}

void SceneObject::setScale(const QVector3D& scale)
{
    if (m_locked) {
        qWarning() << "Cannot modify locked object:" << m_name;
        return;
    }

    m_transform->setScale3D(scale);
    emit transformChanged();
}

void SceneObject::setDimensions(const QVector3D& dim)
{
    if (m_locked) {
        qWarning() << "Cannot modify locked object:" << m_name;
        return;
    }

    m_dimensions = dim;

    // Regenerate mesh with new dimensions
    generateMesh();
    updateGeometry();

    emit transformChanged();
}

void SceneObject::setName(const QString& name)
{
    if (m_name != name) {
        m_name = name;
        emit propertiesChanged();
    }
}

void SceneObject::setVisible(bool visible)
{
    if (m_visible != visible) {
        m_visible = visible;
        setEnabled(visible);  // Qt3D visibility
        emit propertiesChanged();
    }
}

void SceneObject::setLocked(bool locked)
{
    if (m_locked != locked) {
        m_locked = locked;
        emit propertiesChanged();
    }
}

void SceneObject::setMaterialId(int id)
{
    if (m_materialId != id) {
        m_materialId = id;
        emit propertiesChanged();
    }
}

void SceneObject::updateGeometry()
{
    if (!m_renderer || !m_meshData) {
        qWarning() << "Cannot update geometry: renderer or mesh data is null";
        return;
    }

    // Generate new Qt3D geometry from mesh data
    Qt3DCore::QGeometry* geometry = m_meshData->generateGeometry(this);
    if (geometry) {
        m_renderer->setGeometry(geometry);
        qDebug() << "Geometry updated for" << m_name;
    }
}

void SceneObject::setSelected(bool selected)
{
    if (m_selected != selected) {
        m_selected = selected;
        emit selectionChanged(selected);

        // Update material to show selection (orange highlight)
        if (m_material) {
            auto* phongMaterial = qobject_cast<Qt3DExtras::QPhongMaterial*>(m_material);
            if (phongMaterial) {
                if (selected) {
                    phongMaterial->setDiffuse(QColor(255, 140, 0));  // Orange
                    phongMaterial->setAmbient(QColor(127, 70, 0));
                } else {
                    phongMaterial->setDiffuse(QColor(120, 150, 220));  // Default blue
                    phongMaterial->setAmbient(QColor(60, 75, 110));
                }
            }
        }
    }
}

void SceneObject::onObjectClicked()
{
    qDebug() << "Object clicked:" << m_name;
    emit clicked(this);
}
