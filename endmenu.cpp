#include "endmenu.h"
#include "ui_endmenu.h"

#include "mainwindow.h"
EndMenu::EndMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EndMenu)
{
    ui->setupUi(this);
}

EndMenu::~EndMenu()
{
    delete ui;
}

void EndMenu::on_pushButton_clicked()
{
    MainWindow* main_window = qobject_cast<MainWindow*>(parent());
    if (main_window) main_window->Restart();
}

