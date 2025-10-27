#ifndef VIEWPORTSETTINGS_H
#define VIEWPORTSETTINGS_H

#include <QObject>
#include <QColor>

class ViewportSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool showGrid READ showGrid WRITE setShowGrid NOTIFY showGridChanged)
    Q_PROPERTY(bool showAxis READ showAxis WRITE setShowAxis NOTIFY showAxisChanged)
    Q_PROPERTY(float gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
    Q_PROPERTY(int gridDivisions READ gridDivisions WRITE setGridDivisions NOTIFY gridDivisionsChanged)
    Q_PROPERTY(float axisLength READ axisLength WRITE setAxisLength NOTIFY axisLengthChanged)

public:
    explicit ViewportSettings(QObject *parent = nullptr);

    // Grid settings
    bool showGrid() const { return m_showGrid; }
    void setShowGrid(bool show);

    float gridSize() const { return m_gridSize; }
    void setGridSize(float size);

    int gridDivisions() const { return m_gridDivisions; }
    void setGridDivisions(int divisions);

    QColor gridColor() const { return m_gridColor; }
    void setGridColor(const QColor &color);

    // Axis settings
    bool showAxis() const { return m_showAxis; }
    void setShowAxis(bool show);

    float axisLength() const { return m_axisLength; }
    void setAxisLength(float length);

    float axisThickness() const { return m_axisThickness; }
    void setAxisThickness(float thickness);

    // Navigation settings
    bool invertPanX() const { return m_invertPanX; }
    void setInvertPanX(bool invert) { m_invertPanX = invert; }

    bool invertPanY() const { return m_invertPanY; }
    void setInvertPanY(bool invert) { m_invertPanY = invert; }

    float panSensitivity() const { return m_panSensitivity; }
    void setPanSensitivity(float sensitivity) { m_panSensitivity = sensitivity; }

    float orbitSensitivity() const { return m_orbitSensitivity; }
    void setOrbitSensitivity(float sensitivity) { m_orbitSensitivity = sensitivity; }

    float zoomSensitivity() const { return m_zoomSensitivity; }
    void setZoomSensitivity(float sensitivity) { m_zoomSensitivity = sensitivity; }

    // Background
    QColor backgroundColor() const { return m_backgroundColor; }
    void setBackgroundColor(const QColor &color);

    // Camera
    float nearPlane() const { return m_nearPlane; }
    void setNearPlane(float near) { m_nearPlane = near; }

    float farPlane() const { return m_farPlane; }
    void setFarPlane(float far) { m_farPlane = far; }

    float fieldOfView() const { return m_fieldOfView; }
    void setFieldOfView(float fov) { m_fieldOfView = fov; }

signals:
    void showGridChanged();
    void showAxisChanged();
    void gridSizeChanged();
    void gridDivisionsChanged();
    void axisLengthChanged();
    void backgroundColorChanged();

private:
    // Grid
    bool m_showGrid;
    float m_gridSize;      // Size in meters (1m default)
    int m_gridDivisions;   // Number of grid lines
    QColor m_gridColor;

    // Axis
    bool m_showAxis;
    float m_axisLength;    // Length of axis lines
    float m_axisThickness;

    // Navigation
    bool m_invertPanX;
    bool m_invertPanY;
    float m_panSensitivity;
    float m_orbitSensitivity;
    float m_zoomSensitivity;

    // Background
    QColor m_backgroundColor;

    // Camera
    float m_nearPlane;
    float m_farPlane;
    float m_fieldOfView;
};

#endif // VIEWPORTSETTINGS_H