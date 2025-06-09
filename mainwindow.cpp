#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QResizeEvent>

#include "gameprocess.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setFixedSize(800, 600);
    // setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGameProcess(GameProcess* game_process) {
    this->game_process = game_process;
}

void MainWindow::Start() {
    game_process->Start();
}

void MainWindow::Restart() {
    game_process->Restart();
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    QMainWindow::mousePressEvent(event);
    game_process->mousePressEvent(event);
}
