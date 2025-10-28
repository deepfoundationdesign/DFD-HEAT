#include "CrosshairsOverlay.h"
#include <QPainter>
#include <QPaintEvent>

CrosshairsOverlay::CrosshairsOverlay(QWidget *parent)
    : QWidget(parent)
    , m_crosshairSize(15)      // Length of each line from center
    , m_crosshairGap(3)        // Gap in the center
    , m_crosshairThickness(2)  // Line thickness
    , m_crosshairColor(255, 255, 255, 200)  // White with slight transparency
{
    // Make the widget transparent and ignore mouse events
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    setVisible(false);  // Hidden by default
}

void CrosshairsOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Get center of widget
    int centerX = width() / 2;
    int centerY = height() / 2;

    // Setup pen
    QPen pen(m_crosshairColor);
    pen.setWidth(m_crosshairThickness);
    painter.setPen(pen);

    // Draw horizontal line (left and right of center)
    painter.drawLine(centerX - m_crosshairSize, centerY,
                    centerX - m_crosshairGap, centerY);
    painter.drawLine(centerX + m_crosshairGap, centerY,
                    centerX + m_crosshairSize, centerY);

    // Draw vertical line (top and bottom of center)
    painter.drawLine(centerX, centerY - m_crosshairSize,
                    centerX, centerY - m_crosshairGap);
    painter.drawLine(centerX, centerY + m_crosshairGap,
                    centerX, centerY + m_crosshairSize);

    // Draw center dot
    painter.setBrush(m_crosshairColor);
    painter.drawEllipse(QPoint(centerX, centerY), 1, 1);
}
