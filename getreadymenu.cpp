#include "getreadymenu.h"
#include "ui_getreadymenu.h"

GetReadyMenu::GetReadyMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GetReadyMenu)
{
    ui->setupUi(this);
}

GetReadyMenu::~GetReadyMenu()
{
    delete ui;
}
