#include "mainwindow.h"
#include "ui_mainwindow.h"

const int PaintWidget::basic[3][3] = { {8, 8, 10}, {16, 16, 40}, {16, 30, 99} };
const QString PaintWidget::mode_name[4] = {"E", "M", "H", "C"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    field = new PaintWidget(this);
    setGameFieldGeometry(QDesktopWidget().screenGeometry());
    field->game_mode = 0;
    field->click_mode = 1;
    field->colors = {Qt::black, Qt::blue, Qt::cyan, QColor(0, 0, 100), QColor(100, 100, 0),
              Qt::yellow, Qt::green, Qt::magenta, Qt::red};
    field->images = {
        {"empty_cell", QImage(":/icons/tile.ico")},
        {"smile", QImage(":/icons/smiley1.ico")},
        {"cool_smile", QImage(":/icons/smiley.ico")},
        {"sad_smile", QImage(":/icons/smiley3.ico")},
        {"mine_red", QImage(":/icons/mine.ico")},
        {"mine", QImage(":/icons/mine2.ico")},
        {"flag", QImage(":/icons/flag.ico")},
        {"mine_burst", QImage(":/icons/mine4.ico")},
        {"mine_red_burst", QImage(":/icons/mine3.ico")}
    };
    connect(&field->timer, SIGNAL(timeout()), this, SLOT(update()));
}

void MainWindow::setGameFieldGeometry(QRect geom) {
    if (field->scr_rect == geom)
        return;
    field->scr_rect = geom;
    field->setGeometry(field->scr_rect);

    field->upperPanel = QRect(0, 0, field->scr_rect.width(), (int) (field->scr_rect.height() * .1));
    field->start_btn_rect = QRect((field->upperPanel.width() - field->upperPanel.height()) / 2, 0,
                                 field->upperPanel.height(), field->upperPanel.height());
    field->mode_btn_rect = QRect((field->upperPanel.width() + field->upperPanel.height()) / 2 + 10,
                                 int(field->upperPanel.height() / 7.),
                                 int(5 * field->upperPanel.height() / 7.),
                                 int(5 * field->upperPanel.height() / 7.));
    field->time_rect = QRect(field->mode_btn_rect.right() + 10, 0,
                             field->upperPanel.width() - field->mode_btn_rect.right(),
                             field->upperPanel.height());
    field->points_rect = QRect(0, 0, field->time_rect.width(), field->time_rect.height());
    field->gmode_rect = QRect(int(field->upperPanel.width() - 2 * field->upperPanel.height()) / 2 - 10,
                              int(field->upperPanel.height() / 7.),
                              int(5 * field->upperPanel.height() / 7.),
                              int(5 * field->upperPanel.height() / 7.));
    field->player.setOnScreen(geom.width(), geom.height() - field->upperPanel.height());
}

void MainWindow::resizeEvent(QResizeEvent * event) {
    setGameFieldGeometry(QRect(0, 0, event->size().width(), event->size().height()));
    update();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Menu) {
        this->close();
        QMessageBox::information(this, "About", "This game I was compelled to develop in order to pass \
                                 laboratory work in university. Just quietly play it.\
                                 \n02.03.14\nWitalia");
    }
    if (event->key() == Qt::Key_Back) {
        this->close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void PaintWidget::new_game() {
    if (game_mode == 3) {
        int cur_mode[3];
        QString data_name[3] = {"Width:", "Height:", "Mines number:"};
        for (int i = 0; i < 3; ++i) {
            bool ok;
            cur_mode[i] = QInputDialog::getInt(this, "Custom mode", data_name[i], 10, 10, i == 2 ? 3000 : 50, 1, &ok);
            if (!ok) return;
        }
        player = Game(cur_mode[0], cur_mode[1], cur_mode[2]);
    } else
        player = Game(basic[game_mode][0], basic[game_mode][1], basic[game_mode][2]);
    player.setOnScreen(scr_rect.width(), scr_rect.height() - upperPanel.height());
    if (timer.isActive())
        timer.stop();
    time.restart();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent * event) {
    if (!field->upperPanel.contains(event->pos()) && field->player.isRunning()) {
        auto cd = field->player.getFieldCoord(event->x(), event->y() - field->upperPanel.height());
        field->player.autoOpen(cd.first, cd.second);
        if (field->player.isFinished() && field->timer.isActive())
            field->timer.stop();
    }
}

void MainWindow::mouseReleaseEvent( QMouseEvent * event ) {
    if (field->upperPanel.contains(event->pos())) {
        if (field->start_btn_rect.contains(event->pos())) {
            field->new_game();
        } else if (event->x() < field->upperPanel.width() / 2) {
            field->game_mode = (field->game_mode + 1) % 4;
        } else {
            field->click_mode ^= 1;
        }
    } else {
        auto cd = field->player.getFieldCoord(event->x(), event->y() - field->upperPanel.height());
        field->player.click(cd.first, cd.second, field->click_mode);
        if (field->player.isRunning() && !field->timer.isActive()) {
            field->timer.start(1000);
            field->time.start();
        }
        if (field->player.isFinished() && field->timer.isActive())
            field->timer.stop();
    }
    update();
}

void PaintWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    auto set_font_size = [&](int sz) {
        QFont cur_font = painter.font();
        cur_font.setPixelSize(sz);
        painter.setFont(cur_font);
    };
    if (player.isFinished() == 0)
        painter.drawImage(start_btn_rect, images.find("smile")->second);
    else if (player.isFinished() == 1)
        painter.drawImage(start_btn_rect, images.find("cool_smile")->second);
    else
        painter.drawImage(start_btn_rect, images.find("sad_smile")->second);
    painter.drawImage(mode_btn_rect, images.find(click_mode ? "mine_red": "flag")->second);

    set_font_size(gmode_rect.height());
    painter.drawText(gmode_rect, Qt::AlignCenter, mode_name[game_mode]);
    set_font_size(points_rect.height());
    painter.drawText(points_rect, Qt::AlignCenter, QString::number(player.getMinesCnt()));
    painter.drawText(time_rect, Qt::AlignCenter,
                     QString::number(player.isRunning() && !player.isFinished() ? time.elapsed() / 1000 : 0));

    for (int i = 0; i < player.Width(); ++i) {
        for (int j = 0; j < player.Height(); ++j) {
            QRect cur_rect = QRect(player.getCellSize().first * i, player.getCellSize().second * j + upperPanel.height(),
                                   player.getCellSize().first, player.getCellSize().second);
            if (player.getState(i, j) == Game::States::Flagged) {
                if (player.isFinished() == 2) {
                    if (player.getNumberOnField(i, j) == -1)
                        painter.drawImage(cur_rect, images.find("mine")->second);
                    else {
                        painter.drawImage(cur_rect, images.find("flag")->second);
                        painter.setPen(QPen(QColor(255, 0, 0)));
                        painter.drawRect(cur_rect);
                    }
                } else
                    painter.drawImage(cur_rect, images.find("flag")->second);
            } else if (player.getState(i, j) == Game::States::Untouched) {
                painter.drawImage(cur_rect, images.find("empty_cell")->second);
            } else {
                int cur_number = player.getNumberOnField(i, j);
                painter.setPen(QPen(QColor(0, 0, 0)));
                if (cur_number > 0 && cur_number < 9) {
                    set_font_size(cur_rect.height());
                    painter.setPen(QPen(colors[cur_number]));
                    painter.drawText(cur_rect, Qt::AlignCenter, QString::number(cur_number));
                } else if (cur_number != 0)
                    painter.drawImage(cur_rect,
                                      images.find(string("mine_") + (cur_number == -2 ? "red_" : "") + "burst")->second);
            }
        }
    }
}
