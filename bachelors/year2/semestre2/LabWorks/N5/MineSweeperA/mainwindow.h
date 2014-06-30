#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QTime>
#include <QTimer>
#include <QDesktopWidget>
#include <QInputDialog>
#include <unordered_map>
#include <iostream>
#include <string>
#include "game.h"

using namespace std;

class PaintWidget : public QWidget {
    QRect scr_rect;
    QRect upperPanel;
    QRect start_btn_rect;
    QRect mode_btn_rect;
    QRect time_rect;
    QRect points_rect;
    QRect gmode_rect;
    int click_mode;
    int game_mode;
    Game player;
    QTime time;
    QTimer timer;
    vector<QColor> colors;
    unordered_map<string, QImage> images;
    static const int basic[3][3];
    static const QString mode_name[4];
    friend class MainWindow;
public:
    void new_game();
    PaintWidget(QWidget *arg) : QWidget(arg) {}
    void paintEvent(QPaintEvent*);
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void mouseReleaseEvent ( QMouseEvent * );
    void mouseDoubleClickEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void keyReleaseEvent(QKeyEvent *);
private:
    void setGameFieldGeometry(QRect);
    Ui::MainWindow *ui;
    PaintWidget *field;
};

#endif // MAINWINDOW_H
