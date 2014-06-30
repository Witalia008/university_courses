#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QInputDialog>
#include <QMouseEvent>
#include <string>

#include "clientpane.h"
#include "serverpane.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    int start();
    int startServer();
    int startClient();
    void resizeEvent(QResizeEvent *);
private:
    Ui::MainWindow *ui;
    Pane *pane;
};

#endif // MAINWINDOW_H
