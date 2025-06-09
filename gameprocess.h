#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <unordered_set>

#include <QMainWindow>
#include <QObject>
#include <QTimer>
#include <QPushButton>
#include <QtMultimedia/QSoundEffect>

#include "flappybird.h"
#include "scoredisplay.h"

class GameProcess : public QObject
{
    Q_OBJECT

public:
    GameProcess(QWidget* main_window);
    ~GameProcess() override;
    void Start();
    void Restart();
    void mousePressEvent(QMouseEvent* event);

private:
    QWidget* main_window = nullptr;
    QWidget* menu = nullptr;
    QLabel* background = nullptr;

    QSoundEffect* operate_sound_effect = nullptr;
    QSoundEffect* score_sound_effect = nullptr;

    std::unordered_set<QWidget*> scrolled_widgets;
    void widgetsScroll(bool scroll);
    int scroll_interval; // ms
    QTimer* scroll_timer = nullptr;

    FlappyBird* flappy_bird;

    int game_state = 0;

    void Run();
    void Fly();
    QTimer* game_timer = nullptr;
    QTimer* fly_timer = nullptr;

    int score = 0, best_score = 0, game_time = 0;
    ScoreDisplay* score_display = nullptr;
    std::unordered_set<QWidget*> obstacles;
    int last_hole_pos = -1;

    void End();

    const int GROUND_AMOUNT = 2;
    const QSize MAP_SIZE = QSize(288, 400);
    const QSize BIRD_SIZE = QSize(34, 24);
    const int MARGIN = 80;
    const int HOLE_HEIGHT = 100;
    const int MSPF = 16;
};

#endif // GAMEPROCESS_H
