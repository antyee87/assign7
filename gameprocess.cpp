#include "gameprocess.h"

#include <math.h>
#include <vector>

#include <QTimer>
#include <QLabel>
#include <QRandomGenerator>
#include <QAudioDevice>

#include "startmenu.h"
#include "getreadymenu.h"
#include "endmenu.h"
#include "scoredisplay2.h"

GameProcess::GameProcess(QWidget* main_window)
    :QObject(main_window) {
    this->main_window = main_window;

    operate_sound_effect = new QSoundEffect(main_window);
    score_sound_effect = new QSoundEffect(main_window);

    operate_sound_effect->setSource(QUrl("qrc:/resources/sound/sfx_point.wav"));
    score_sound_effect->setSource(QUrl("qrc:/resources/sound/sfx_point.wav"));

    // background initialize
    QPixmap background_pixmap = QPixmap(":/resources/image/bg_day.png");
    scroll_interval = 4000 / (main_window->size().width() / 3);

    background = new QLabel(main_window);
    background->resize(background_pixmap.size());
    background->setPixmap(background_pixmap);
    background->move(0, 0);
    background->show();

    QPixmap ground_pixmap = QPixmap(":/resources/image/ground.png");
    QPoint pos = QPoint(0, main_window->size().height() - ground_pixmap.size().height());
    for (int i = 0; i < GROUND_AMOUNT; ++i) {
        QLabel* ground = new QLabel(main_window);
        ground->resize(ground_pixmap.size());
        ground->setPixmap(ground_pixmap);
        ground->setProperty("isGround", true);
        ground->move(pos);
        pos += QPoint(ground->width(), 0);
        ground->show();
        scrolled_widgets.insert(ground);
        obstacles.insert(ground);
    }
    widgetsScroll(true);

    flappy_bird = new FlappyBird(main_window);
    flappy_bird->move(
        QPoint((MAP_SIZE.width() -  BIRD_SIZE.width()) / 2,
               (MAP_SIZE.height() -  BIRD_SIZE.height()) / 2));
    flappy_bird->show();

    menu = new StartMenu(main_window);
    menu->setObjectName("StartMenu");
    menu->raise();
    menu->show();
}

void GameProcess::widgetsScroll(bool scroll) {
    if (!scroll_timer) {
        scroll_timer = new QTimer(this);
        connect(scroll_timer, &QTimer::timeout, this, [&]() {
            std::vector<QWidget*> will_remove;
            for (auto& widget : scrolled_widgets) {
                if (!widget) continue;
                widget->move(widget->x() - 4, widget->y());
                if (widget->x() + widget->width() <= 0) {
                    if (widget->property("isGround").toBool()) {
                        widget->move(widget->x() + widget->width() * GROUND_AMOUNT, widget->y());
                    } else {
                        will_remove.push_back(widget);
                    }

                }
                if (widget->property("hasScore").toBool()) {
                    if (widget->x() + widget->width() < flappy_bird->x()) {
                        score_display->setScore(++score);
                        widget->setProperty("hasScore", false);
                        score_sound_effect->setSource(QUrl("qrc:/resources/sound/sfx_point.wav"));
                        if (!score_sound_effect->audioDevice().isNull()) score_sound_effect->play();

                    }
                }
            }
            for (auto& widget : will_remove) {
                widget->deleteLater();
                scrolled_widgets.erase(widget);
                obstacles.erase(widget);
            }
        });
    }
    if (scroll) scroll_timer->start(scroll_interval);
    else scroll_timer->stop();
}

void GameProcess::Start() {
    game_state = 1;
    score = 0;

    menu->deleteLater();
    menu = new GetReadyMenu(main_window);
    menu->show();

    flappy_bird->setRotation(0);
    flappy_bird->setSpeed(0);
    flappy_bird->move(
        QPoint(MAP_SIZE.width() / 4 - BIRD_SIZE.width() / 2,
               (MAP_SIZE.height() -  BIRD_SIZE.height()) / 2));

    score_display = new ScoreDisplay(main_window);
    score_display->setScore(score);
    score_display->move((MAP_SIZE.width() - score_display->width()) / 2, 10);
    score_display->show();
}

void GameProcess::Fly() {
    flappy_bird->move(flappy_bird->pos() + QPoint(0, flappy_bird->getSpeed()));
    if (flappy_bird->y() < 0) flappy_bird->move(flappy_bird->x(), 0);
    for (auto& obstacle : obstacles) {
        if (!obstacle) continue;
        if (flappy_bird->geometry().intersects(obstacle->geometry())) {
            if (obstacle->property("isGround").toBool()) fly_timer->stop();
        }
    }
    flappy_bird->setSpeed(std::min(flappy_bird->getSpeed() + 0.4, 12.0));
}

void GameProcess::Run() {
    for (auto& obstacle : obstacles) {
        if (!obstacle) continue;
        if (flappy_bird->geometry().intersects(obstacle->geometry())) {
            game_state = 3;
            operate_sound_effect->setSource(QUrl("qrc:/resources/sound/sfx_hit.wav"));
            if (!score_sound_effect->audioDevice().isNull()) operate_sound_effect->play();
            scroll_timer->stop();
            game_timer->stop();
            End();
        }
    }

    if ((game_time - 2000 / MSPF) % (2000 / MSPF) == 0) {
        int hole_pos = 0;
        if (last_hole_pos == -1) {
            hole_pos = QRandomGenerator::global()->bounded(MARGIN, MAP_SIZE.height() - MARGIN);
        } else {
            hole_pos = last_hole_pos + QRandomGenerator::global()->bounded(-40, 40);
            hole_pos = std::max(MARGIN, std::min(hole_pos, MAP_SIZE.height() - MARGIN));
        }
        QLabel* pipe_up = new ResizeablePicture(main_window, QPixmap(":/resources/image/pipe_up.png"));
        pipe_up->move(MAP_SIZE.width(), hole_pos + HOLE_HEIGHT / 2);
        pipe_up->lower();
        pipe_up->setProperty("hasScore", true);
        pipe_up->setProperty("isPipe", true);
        pipe_up->show();
        scrolled_widgets.insert(pipe_up);
        obstacles.insert(pipe_up);

        QLabel* pipe_down = new ResizeablePicture(main_window, QPixmap(":/resources/image/pipe_down.png"));
        pipe_down->move(MAP_SIZE.width(), hole_pos - HOLE_HEIGHT / 2 - pipe_down->height());
        pipe_down->lower();
        pipe_down->setProperty("isPipe", true);
        pipe_down->show();
        scrolled_widgets.insert(pipe_down);
        obstacles.insert(pipe_down);

        background->lower();
    }

    ++game_time;
}

void GameProcess::mousePressEvent(QMouseEvent* event) {
    if (game_state == 1) {

        if (!game_timer) {
            game_timer = new QTimer();
            connect(game_timer, &QTimer::timeout, this, &GameProcess::Run);
        }
        game_time = 0;
        game_timer->start(MSPF);

        if (!fly_timer) {
            fly_timer = new QTimer();
            connect(fly_timer, &QTimer::timeout, this, &GameProcess::Fly);
        }
        fly_timer->start(MSPF);
        Fly();
        QTimer::singleShot(MSPF, this, [&](){
            menu->hide();
        });
        game_state = 2;

    }
    if (game_state == 2) {
        flappy_bird->setSpeed(-6);
        operate_sound_effect->setSource(QUrl("qrc:/resources/sound/sfx_wing.wav"));
        if (!score_sound_effect->audioDevice().isNull()) operate_sound_effect->play();
    }
}

void GameProcess::End() {
    best_score = std::max(score, best_score);
    flappy_bird->toggleFlapping();

    score_display->hide();
    menu->deleteLater();
    menu = new EndMenu(main_window);
    menu->show();
    ScoreDisplay2* current_score_display = new ScoreDisplay2(menu);
    current_score_display->move(190, 195);
    current_score_display->setScore(score);
    current_score_display->show();

    ScoreDisplay2* best_score_display = new ScoreDisplay2(menu);
    best_score_display->move(190, 235);
    best_score_display->setScore(best_score);
    best_score_display->show();

    int rank = std::min(score / 10 - 1, 40);
    if (rank >= 0) {
        QPixmap original(":/resources/image/medals.png");
        QPixmap cropped = original.copy(rank * 44, 0, 44, 44);
        QLabel* medal = new QLabel(menu);
        medal->resize(44, 44);
        medal->move(63, 205);
        medal->setPixmap(cropped);
        medal->raise();
        medal->show();
    }
}

void GameProcess::Restart() {
    std::vector<QWidget*> will_remove;
    for (auto& widget : scrolled_widgets) {
        if (widget->property("isPipe").toBool()) {
            will_remove.push_back(widget);
        }
    }
    for (auto& widget : will_remove) {
        widget->deleteLater();
        scrolled_widgets.erase(widget);
        obstacles.erase(widget);
    }

    flappy_bird->toggleFlapping();
    scroll_timer->start(scroll_interval);
    fly_timer->stop();
    Start();
}

GameProcess::~GameProcess() {

}
