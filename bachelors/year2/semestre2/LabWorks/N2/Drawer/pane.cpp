#include "pane.h"

Pane::Pane(QWidget *parent) :
    QWidget(parent)
{
    paintArea = QRect(0, 15, parent->width(), parent->height() - 15);
    pixmap = new QPixmap(paintArea.size());
    painter = new QPainter(pixmap);
    draw(PaintType::CLEAR, QPoint(), QPoint(), Qt::white, Qt::blue);
}

void Pane::draw(PaintType type, QPoint from, QPoint to, QColor brush, QColor pen) {
    painter->setBrush(QBrush(brush));
    painter->setPen(QPen(pen));
    if (type == PaintType::CLEAR) {
        painter->setPen(Qt::PenStyle::NoPen);
        painter->drawRect(0, 0, paintArea.width(), paintArea.height());
    } else if (type == PaintType::ELLIPSE) {
        painter->drawEllipse(QRect(from, to));
    } else if (type == PaintType::RECTANGLE) {
        painter->drawRect(QRect(from, to));
    } else if (type == PaintType::LINE) {
        painter->drawLine(from, to);
    }
    update();
}

void Pane::paintEvent(QPaintEvent *)
{
    QPainter pt(this);
    pt.drawPixmap(paintArea, *pixmap);
}

void Pane::resizeEvent(QResizeEvent *event)
{
    paintArea = QRect(QPoint(0, 0), event->size());
}
