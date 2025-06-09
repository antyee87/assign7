#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class GameProcess;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setGameProcess(GameProcess* game_process);
    void Start();
    void Restart();

private:
    Ui::MainWindow *ui;
    GameProcess* game_process = nullptr;

protected:
    void mousePressEvent(QMouseEvent* event) override;
};
#endif // MAINWINDOW_H
