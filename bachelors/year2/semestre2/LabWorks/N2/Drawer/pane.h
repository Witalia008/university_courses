#ifndef PANE_H
#define PANE_H

#include <QWidget>
#include <QPainter>
#include <string>
#include <thread>
#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>
#include "mysocket.h"
#include "datahandler.h"

using namespace std;

class Pane : public QWidget
{
    Q_OBJECT
public:
    enum class PaintType {CLEAR, COPY, RESIZE, ELLIPSE, RECTANGLE, LINE, PENSIL};
public:
    explicit Pane(QWidget *parent = 0);
    void draw(PaintType, QPoint, QPoint, QColor = Qt::white, QColor = Qt::black);
public slots:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void updQueue() {}
protected:
    QPainter *painter;
    QPixmap *pixmap;
    QRect paintArea;
};

#endif // PANE_H
