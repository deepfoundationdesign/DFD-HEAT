#include "viewport/ViewportSettings.h"

ViewportSettings::ViewportSettings(QObject *parent)
    : QObject(parent)
    , m_showGrid(true)
    , m_gridSize(1.0f)       // 1 meter grid
    , m_gridDivisions(20)     // 20x20 grid
    , m_gridColor(128, 128, 128, 100)
    , m_showAxis(true)
    , m_axisLength(1000.0f)   // Extends towards "infinity"
    , m_axisThickness(0.01f)
    , m_invertPanX(false)     // Fixed: not inverted by default
    , m_invertPanY(false)     // Fixed: not inverted by default
    , m_panSensitivity(1.0f)
    , m_orbitSensitivity(1.0f)
    , m_zoomSensitivity(1.0f)
    , m_backgroundColor(60, 60, 60)
    , m_nearPlane(0.01f)
    , m_farPlane(10000.0f)
    , m_fieldOfView(45.0f)
{
}

void ViewportSettings::setShowGrid(bool show)
{
    if (m_showGrid != show) {
        m_showGrid = show;
        emit showGridChanged();
    }
}

void ViewportSettings::setGridSize(float size)
{
    if (!qFuzzyCompare(m_gridSize, size)) {
        m_gridSize = size;
        emit gridSizeChanged();
    }
}

void ViewportSettings::setGridDivisions(int divisions)
{
    if (m_gridDivisions != divisions) {
        m_gridDivisions = divisions;
        emit gridDivisionsChanged();
    }
}

void ViewportSettings::setGridColor(const QColor &color)
{
    if (m_gridColor != color) {
        m_gridColor = color;
    }
}

void ViewportSettings::setShowAxis(bool show)
{
    if (m_showAxis != show) {
        m_showAxis = show;
        emit showAxisChanged();
    }
}

void ViewportSettings::setAxisLength(float length)
{
    if (!qFuzzyCompare(m_axisLength, length)) {
        m_axisLength = length;
        emit axisLengthChanged();
    }
}

void ViewportSettings::setAxisThickness(float thickness)
{
    if (!qFuzzyCompare(m_axisThickness, thickness)) {
        m_axisThickness = thickness;
    }
}

void ViewportSettings::setBackgroundColor(const QColor &color)
{
    if (m_backgroundColor != color) {
        m_backgroundColor = color;
        emit backgroundColorChanged();
    }
}