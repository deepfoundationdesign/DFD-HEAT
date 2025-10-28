#include "PropertiesPanel.h"
#include "SceneObject.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QDebug>

PropertiesPanel::PropertiesPanel(QWidget *parent)
    : QWidget(parent)
    , m_currentObject(nullptr)
{
    setupUI();
}

PropertiesPanel::~PropertiesPanel()
{
}

void PropertiesPanel::setupUI()
{
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(10);

    // Object Properties Group
    auto* objGroup = new QGroupBox("Object Properties");
    auto* objLayout = new QGridLayout(objGroup);

    objLayout->addWidget(new QLabel("Name:"), 0, 0);
    m_nameEdit = new QLineEdit();
    objLayout->addWidget(m_nameEdit, 0, 1);

    objLayout->addWidget(new QLabel("UUID:"), 1, 0);
    m_uuidLabel = new QLabel("-");
    m_uuidLabel->setWordWrap(true);
    m_uuidLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    objLayout->addWidget(m_uuidLabel, 1, 1);

    m_visibleCheck = new QCheckBox("Visible");
    objLayout->addWidget(m_visibleCheck, 2, 0);

    m_lockedCheck = new QCheckBox("Locked");
    objLayout->addWidget(m_lockedCheck, 2, 1);

    mainLayout->addWidget(objGroup);

    // Transform Properties Group
    auto* transformGroup = new QGroupBox("Transform");
    auto* transformLayout = new QGridLayout(transformGroup);

    // Helper lambda for creating spin boxes
    auto createSpinBox = [](double min, double max, int decimals) {
        auto* spinBox = new QDoubleSpinBox();
        spinBox->setRange(min, max);
        spinBox->setDecimals(decimals);
        spinBox->setSingleStep(0.1);
        return spinBox;
    };

    // Location
    int row = 0;
    transformLayout->addWidget(new QLabel("Location:"), row, 0);
    transformLayout->addWidget(new QLabel("X:"), row, 1);
    m_locationX = createSpinBox(-1000, 1000, 2);
    transformLayout->addWidget(m_locationX, row, 2);
    transformLayout->addWidget(new QLabel("Y:"), row, 3);
    m_locationY = createSpinBox(-1000, 1000, 2);
    transformLayout->addWidget(m_locationY, row, 4);
    transformLayout->addWidget(new QLabel("Z:"), row, 5);
    m_locationZ = createSpinBox(-1000, 1000, 2);
    transformLayout->addWidget(m_locationZ, row, 6);

    // Rotation
    row++;
    transformLayout->addWidget(new QLabel("Rotation:"), row, 0);
    transformLayout->addWidget(new QLabel("X:"), row, 1);
    m_rotationX = createSpinBox(-360, 360, 1);
    transformLayout->addWidget(m_rotationX, row, 2);
    transformLayout->addWidget(new QLabel("Y:"), row, 3);
    m_rotationY = createSpinBox(-360, 360, 1);
    transformLayout->addWidget(m_rotationY, row, 4);
    transformLayout->addWidget(new QLabel("Z:"), row, 5);
    m_rotationZ = createSpinBox(-360, 360, 1);
    transformLayout->addWidget(m_rotationZ, row, 6);

    // Scale
    row++;
    transformLayout->addWidget(new QLabel("Scale:"), row, 0);
    transformLayout->addWidget(new QLabel("X:"), row, 1);
    m_scaleX = createSpinBox(0.01, 100, 2);
    m_scaleX->setValue(1.0);
    transformLayout->addWidget(m_scaleX, row, 2);
    transformLayout->addWidget(new QLabel("Y:"), row, 3);
    m_scaleY = createSpinBox(0.01, 100, 2);
    m_scaleY->setValue(1.0);
    transformLayout->addWidget(m_scaleY, row, 4);
    transformLayout->addWidget(new QLabel("Z:"), row, 5);
    m_scaleZ = createSpinBox(0.01, 100, 2);
    m_scaleZ->setValue(1.0);
    transformLayout->addWidget(m_scaleZ, row, 6);

    // Dimensions
    row++;
    transformLayout->addWidget(new QLabel("Dimensions:"), row, 0);
    transformLayout->addWidget(new QLabel("X:"), row, 1);
    m_dimensionsX = createSpinBox(0.01, 1000, 2);
    transformLayout->addWidget(m_dimensionsX, row, 2);
    transformLayout->addWidget(new QLabel("Y:"), row, 3);
    m_dimensionsY = createSpinBox(0.01, 1000, 2);
    transformLayout->addWidget(m_dimensionsY, row, 4);
    transformLayout->addWidget(new QLabel("Z:"), row, 5);
    m_dimensionsZ = createSpinBox(0.01, 1000, 2);
    transformLayout->addWidget(m_dimensionsZ, row, 6);

    mainLayout->addWidget(transformGroup);

    // Add stretch at the bottom
    mainLayout->addStretch();

    // Connect signals
    connect(m_nameEdit, &QLineEdit::editingFinished, this, &PropertiesPanel::onNameChanged);

    connect(m_locationX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onLocationChanged);
    connect(m_locationY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onLocationChanged);
    connect(m_locationZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onLocationChanged);

    connect(m_rotationX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onRotationChanged);
    connect(m_rotationY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onRotationChanged);
    connect(m_rotationZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onRotationChanged);

    connect(m_scaleX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onScaleChanged);
    connect(m_scaleY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onScaleChanged);
    connect(m_scaleZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onScaleChanged);

    connect(m_dimensionsX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onDimensionsChanged);
    connect(m_dimensionsY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onDimensionsChanged);
    connect(m_dimensionsZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PropertiesPanel::onDimensionsChanged);

    connect(m_visibleCheck, &QCheckBox::stateChanged, this, &PropertiesPanel::onVisibleChanged);
    connect(m_lockedCheck, &QCheckBox::stateChanged, this, &PropertiesPanel::onLockedChanged);

    // Disable by default (no object selected)
    setEnabled(false);
}

void PropertiesPanel::setObject(SceneObject* object)
{
    // Disconnect from previous object
    if (m_currentObject) {
        disconnect(m_currentObject, nullptr, this, nullptr);
    }

    m_currentObject = object;

    if (m_currentObject) {
        // Connect to object signals
        connect(m_currentObject, &SceneObject::transformChanged, this, &PropertiesPanel::onObjectTransformChanged);
        connect(m_currentObject, &SceneObject::propertiesChanged, this, &PropertiesPanel::onObjectPropertiesChanged);

        // Update UI
        updateFromObject();
        setEnabled(true);
    } else {
        setEnabled(false);
    }
}

void PropertiesPanel::clearObject()
{
    setObject(nullptr);
}

void PropertiesPanel::updateFromObject()
{
    if (!m_currentObject) return;

    blockSignalsTemporarily(true);

    // Object properties
    m_nameEdit->setText(m_currentObject->name());
    m_uuidLabel->setText(m_currentObject->uuid().toString());
    m_visibleCheck->setChecked(m_currentObject->isVisible());
    m_lockedCheck->setChecked(m_currentObject->isLocked());

    // Location
    QVector3D loc = m_currentObject->location();
    m_locationX->setValue(loc.x());
    m_locationY->setValue(loc.y());
    m_locationZ->setValue(loc.z());

    // Rotation
    QVector3D rot = m_currentObject->rotation();
    m_rotationX->setValue(rot.x());
    m_rotationY->setValue(rot.y());
    m_rotationZ->setValue(rot.z());

    // Scale
    QVector3D scale = m_currentObject->scale();
    m_scaleX->setValue(scale.x());
    m_scaleY->setValue(scale.y());
    m_scaleZ->setValue(scale.z());

    // Dimensions
    QVector3D dim = m_currentObject->dimensions();
    m_dimensionsX->setValue(dim.x());
    m_dimensionsY->setValue(dim.y());
    m_dimensionsZ->setValue(dim.z());

    blockSignalsTemporarily(false);
}

void PropertiesPanel::blockSignalsTemporarily(bool block)
{
    m_nameEdit->blockSignals(block);
    m_locationX->blockSignals(block);
    m_locationY->blockSignals(block);
    m_locationZ->blockSignals(block);
    m_rotationX->blockSignals(block);
    m_rotationY->blockSignals(block);
    m_rotationZ->blockSignals(block);
    m_scaleX->blockSignals(block);
    m_scaleY->blockSignals(block);
    m_scaleZ->blockSignals(block);
    m_dimensionsX->blockSignals(block);
    m_dimensionsY->blockSignals(block);
    m_dimensionsZ->blockSignals(block);
    m_visibleCheck->blockSignals(block);
    m_lockedCheck->blockSignals(block);
}

void PropertiesPanel::onNameChanged()
{
    if (m_currentObject) {
        m_currentObject->setName(m_nameEdit->text());
    }
}

void PropertiesPanel::onLocationChanged()
{
    if (m_currentObject) {
        QVector3D loc(m_locationX->value(), m_locationY->value(), m_locationZ->value());
        m_currentObject->setLocation(loc);
    }
}

void PropertiesPanel::onRotationChanged()
{
    if (m_currentObject) {
        QVector3D rot(m_rotationX->value(), m_rotationY->value(), m_rotationZ->value());
        m_currentObject->setRotation(rot);
    }
}

void PropertiesPanel::onScaleChanged()
{
    if (m_currentObject) {
        QVector3D scale(m_scaleX->value(), m_scaleY->value(), m_scaleZ->value());
        m_currentObject->setScale(scale);
    }
}

void PropertiesPanel::onDimensionsChanged()
{
    if (m_currentObject) {
        QVector3D dim(m_dimensionsX->value(), m_dimensionsY->value(), m_dimensionsZ->value());
        m_currentObject->setDimensions(dim);
    }
}

void PropertiesPanel::onVisibleChanged(int state)
{
    if (m_currentObject) {
        m_currentObject->setVisible(state == Qt::Checked);
    }
}

void PropertiesPanel::onLockedChanged(int state)
{
    if (m_currentObject) {
        m_currentObject->setLocked(state == Qt::Checked);
    }
}

void PropertiesPanel::onObjectTransformChanged()
{
    updateFromObject();
}

void PropertiesPanel::onObjectPropertiesChanged()
{
    updateFromObject();
}
