#include "serverpane.h"

ServerPane::ServerPane(QWidget *parent, string port)
    : Pane(parent), socket(port)
{
    std::thread x = std::thread(checkPendingConnections, ref(socket));
    x.detach();
    type = PaintType::ELLIPSE;
    typeSelect = new QComboBox(this);
    types = {{"Ellipse", PaintType::ELLIPSE},
             {"Rectangle", PaintType::RECTANGLE},
             {"Line", PaintType::LINE},
             {"Pensil", PaintType::PENSIL},
             {"Clear", PaintType::CLEAR},
            };
    for (auto i : types)
        typeSelect->addItem(QString(i.first.c_str()));
    brush = Qt::red;
    pen = Qt::blue;
}

void ServerPane::sendChanges(Pane::PaintType type, QPoint from, QPoint to, QColor brush, QColor pen)
{
    DataHandler data;
    data.push_back(static_cast<int>(type));
    data.push_back(from.x());
    data.push_back(from.y());
    data.push_back(to.x());
    data.push_back(to.y());
    data.push_back({brush.red(), brush.green(), brush.blue()});
    data.push_back({pen.red(), pen.green(), pen.blue()});
    socket.send(data.getSendData());
}

void ServerPane::mousePressEvent(QMouseEvent *event)
{
    if (event->y() < typeSelect->height()) {
        if (!typeSelect->geometry().contains(event->pos())) {
            QColorDialog *diag = new QColorDialog(this);
            if (brushRect.contains(event->pos()))
                brush = diag->getColor();
            else
                pen = diag->getColor();
        }
        return;
    }
    firstPt = QPoint(event->x(), event->y() - typeSelect->height());
}

void ServerPane::mouseReleaseEvent(QMouseEvent *event)
{
    type = types[typeSelect->currentIndex()].second;
    secondPt = QPoint(event->x(), event->y() - typeSelect->height());
    if (type != PaintType::PENSIL) {
        QPoint fst = QPoint(min(firstPt.x(), secondPt.x()), min(firstPt.y(), secondPt.y()));
        QPoint snd = QPoint(max(firstPt.x(), secondPt.x()), max(firstPt.y(), secondPt.y()));
        if (type == PaintType::LINE)
            fst = firstPt, snd = secondPt;
        draw(type, fst, snd, brush, pen);
        sendChanges(type, fst, snd, brush, pen);
    } else {
        draw(PaintType::LINE, firstPt, secondPt, brush, pen);
        sendChanges(PaintType::LINE, firstPt, secondPt, brush, pen);
    }
}

void ServerPane::mouseMoveEvent(QMouseEvent *event)
{
    type = types[typeSelect->currentIndex()].second;
    secondPt = QPoint(event->x(), event->y() - typeSelect->height());
    if (type == PaintType::PENSIL) {
        draw(PaintType::LINE, firstPt, secondPt, brush, pen);
        sendChanges(PaintType::LINE, firstPt, secondPt, brush, pen);
        firstPt = secondPt;
    }
}

void ServerPane::resizeEvent(QResizeEvent *event)
{
    typeSelect->setGeometry(0, 0, event->size().width() / 3, 20);
    brushRect = QRect(typeSelect->width(), 0,typeSelect->width(), typeSelect->height());
    penRect = QRect(typeSelect->width() * 2, 0,typeSelect->width(), typeSelect->height());
    paintArea = QRect(QPoint(0, typeSelect->height()), event->size());
    sendChanges(PaintType::RESIZE, paintArea.topLeft(), paintArea.bottomRight());
}

void ServerPane::paintEvent(QPaintEvent *event)
{
    Pane::paintEvent(event);
    QPainter painter(this);
    painter.setBrush(brush);
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(brushRect);
    painter.setBrush(pen);
    painter.drawRect(penRect);
}

void ServerPane::updQueue()
{
    if (socket.nNewConnections()) {
        QImage img;
        socket.wipeNew();
    }
}
