#ifndef GETREADYMENU_H
#define GETREADYMENU_H

#include <QWidget>

namespace Ui {
class GetReadyMenu;
}

class GetReadyMenu : public QWidget
{
    Q_OBJECT

public:
    explicit GetReadyMenu(QWidget *parent = nullptr);
    ~GetReadyMenu();

private:
    Ui::GetReadyMenu *ui;
};

#endif // GETREADYMENU_H
