#include "CrosshairsOverlay.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

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
    setAutoFillBackground(false);  // Don't fill background - stay transparent
    // DO NOT set window flags - this widget is a child overlay, not a separate window!

    setVisible(false);  // Hidden by default
}

void CrosshairsOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    qDebug() << "[CrosshairsOverlay::paintEvent] Painting crosshairs! Size:" << size()
             << "Visible:" << isVisible();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Clear the background to fully transparent
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    // Get center of widget
    int centerX = width() / 2;
    int centerY = height() / 2;

    // Setup pen with bright, solid color for visibility
    QPen pen(QColor(255, 255, 255, 255));  // Fully opaque white
    pen.setWidth(m_crosshairThickness);
    pen.setCapStyle(Qt::RoundCap);
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
    painter.setBrush(QColor(255, 255, 255, 255));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPoint(centerX, centerY), 2, 2);

    qDebug() << "  Drew crosshairs at center:" << centerX << centerY;
}
