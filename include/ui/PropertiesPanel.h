#ifndef PROPERTIESPANEL_H
#define PROPERTIESPANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QLabel>

class SceneObject;

/**
 * @brief Property panel for displaying and editing object properties
 *
 * Shows transform properties (location, rotation, scale, dimensions)
 * and object properties (name, visible, locked) for the selected object.
 */
class PropertiesPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PropertiesPanel(QWidget *parent = nullptr);
    ~PropertiesPanel();

    void setObject(SceneObject* object);
    void clearObject();

private slots:
    void onNameChanged();
    void onLocationChanged();
    void onRotationChanged();
    void onScaleChanged();
    void onDimensionsChanged();
    void onVisibleChanged(int state);
    void onLockedChanged(int state);

    // Update UI when object changes
    void onObjectTransformChanged();
    void onObjectPropertiesChanged();

private:
    void setupUI();
    void updateFromObject();
    void blockSignalsTemporarily(bool block);

    SceneObject* m_currentObject;

    // UI elements
    QLineEdit* m_nameEdit;

    QDoubleSpinBox* m_locationX;
    QDoubleSpinBox* m_locationY;
    QDoubleSpinBox* m_locationZ;

    QDoubleSpinBox* m_rotationX;
    QDoubleSpinBox* m_rotationY;
    QDoubleSpinBox* m_rotationZ;

    QDoubleSpinBox* m_scaleX;
    QDoubleSpinBox* m_scaleY;
    QDoubleSpinBox* m_scaleZ;

    QDoubleSpinBox* m_dimensionsX;
    QDoubleSpinBox* m_dimensionsY;
    QDoubleSpinBox* m_dimensionsZ;

    QCheckBox* m_visibleCheck;
    QCheckBox* m_lockedCheck;

    QLabel* m_uuidLabel;
};

#endif // PROPERTIESPANEL_H
