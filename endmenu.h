#ifndef ENDMENU_H
#define ENDMENU_H

#include <QWidget>

namespace Ui {
class EndMenu;
}

class EndMenu : public QWidget
{
    Q_OBJECT

public:
    explicit EndMenu(QWidget *parent = nullptr);
    ~EndMenu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EndMenu *ui;
};

#endif // ENDMENU_H
