#ifndef CROSSHAIRSOVERLAY_H
#define CROSSHAIRSOVERLAY_H

#include <QWidget>
#include <QPainter>

class CrosshairsOverlay : public QWidget
{
    Q_OBJECT

public:
    explicit CrosshairsOverlay(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_crosshairSize;
    int m_crosshairGap;
    int m_crosshairThickness;
    QColor m_crosshairColor;
};

#endif // CROSSHAIRSOVERLAY_H
