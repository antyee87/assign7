#include "startmenu.h"
#include "ui_startmenu.h"

#include "mainwindow.h"
StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::on_pushButton_clicked()
{
    MainWindow* main_window = qobject_cast<MainWindow*>(parent());
    if (main_window) main_window->Start();
}

