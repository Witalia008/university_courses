#include "clientpane.h"

ClientPane::ClientPane(QWidget *parent, string ip, string port)
    : Pane(parent), socket(ClientSocket(ip, port))
{
    std::thread x = std::thread(checkIncoming, ref(*this));
    x.detach();
    timer = new QTimer();
    timer->start(50);
    connect(timer, SIGNAL(timeout()), SLOT(updQueue()));
}

void ClientPane::resizeEvent(QResizeEvent *event)
{
    paintArea = QRect(QPoint(0, 0), event->size());
}

void ClientPane::updQueue()
{
    while (!Q.empty()) {
        auto cur = Q.front();
        Q.pop();
        if (get<0>(cur) == PaintType::RESIZE)
            resize(get<2>(cur).x(), get<2>(cur).y());
        else {
            draw(get<0>(cur), get<1>(cur), get<2>(cur), get<3>(cur), get<4>(cur));
        }
    }
}


void checkIncoming(ClientPane &item)
{
    for (;;) {
        DataHandler data = DataHandler(item.socket.receive(), true);
        Pane::PaintType type = static_cast<Pane::PaintType>(data.getInt());
        QPoint from = QPoint(data.getInt(), data.getInt());
        QPoint to = QPoint(data.getInt(), data.getInt());
        vector<int> col = {data.getByte(), data.getByte(), data.getByte()};
        QColor brush = QColor(col[0], col[1], col[2]);
        col = {data.getByte(), data.getByte(), data.getByte()};
        QColor pen = QColor(col[0], col[1], col[2]);
        from = QPoint(from.y(), from.x());
        to = QPoint(to.y(), to.x());
        item.Q.push(make_tuple(type, from, to, brush, pen));
    }
}
