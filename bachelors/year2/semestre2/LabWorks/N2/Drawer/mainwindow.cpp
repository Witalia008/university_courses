#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pane = nullptr;
    connect(ui->actionStart_Client, SIGNAL(triggered()), this, SLOT(startClient()));
    connect(ui->actionStart_Server, SIGNAL(triggered()), this, SLOT(startServer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::start() {
    if (pane == nullptr)
        return 1;
    pane->setGeometry(0, ui->menuBar->height(), this->width(),
                      this->height() - ui->menuBar->height());
    pane->show();
}

int MainWindow::startClient() {
    if (pane != nullptr)
        delete pane;
    string ip, port;
    ip = QInputDialog::getText(this, "Enter server's IP", "", QLineEdit::Normal, "127.0.0.1").toStdString();
    port = QInputDialog::getText(this, "Enter connection port", "Enter port (blank if standard)", QLineEdit::Normal, "27015").toStdString();
    pane = new ClientPane(this, ip, port);
    return start();
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    if (pane != nullptr)
        pane->setGeometry(0, ui->menuBar->height(), this->width(),
                      this->height() - ui->menuBar->height());
}

int MainWindow::startServer() {
    if (pane != nullptr)
        delete pane;
    string port = QInputDialog::getText(this, "Enter connection port", "Enter port (blank if standard)", QLineEdit::Normal, "27015").toStdString();
    pane = new ServerPane(this, port);
    return start();
}
