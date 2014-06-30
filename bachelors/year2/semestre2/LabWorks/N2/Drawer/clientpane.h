#ifndef CLIENTPANE_H
#define CLIENTPANE_H

#include <thread>
#include <tuple>
#include <queue>
#include <QTimer>
#include "pane.h"

class ClientPane : public Pane
{
    //Q_OBJECT
private:
    ClientSocket socket;
    queue<tuple<PaintType, QPoint, QPoint, QColor, QColor>> Q;
    QTimer *timer;
public:
    ClientPane(QWidget*, string, string);
    friend void checkIncoming(ClientPane&);
public slots:
    void resizeEvent(QResizeEvent*);
    void updQueue();
};

void checkIncoming(ClientPane&);

#endif // CLIENTPANE_H
