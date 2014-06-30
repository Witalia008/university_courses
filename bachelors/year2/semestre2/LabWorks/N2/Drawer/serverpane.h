#ifndef SERVERPANE_H
#define SERVERPANE_H

#include <QComboBox>
#include <QString>
#include <QColorDialog>
#include <string>
#include "pane.h"

class ServerPane : public Pane
{
    //Q_OBJECT
private:
    ServerSocket socket;
public:
    ServerPane(QWidget*, string);
    void sendChanges(PaintType, QPoint, QPoint, QColor = Qt::white, QColor = Qt::black);
public slots:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void updQueue() override;
protected:
    PaintType type;
    QPoint firstPt, secondPt;
    QColor brush, pen;
    QComboBox *typeSelect;
    QRect brushRect, penRect;
    vector<pair<string, PaintType>> types;
};

#endif // SERVERPANE_H
