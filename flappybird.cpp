#include "flappybird.h"

#include <string>
#include <QPixmap>

FlappyBird::FlappyBird(QWidget* parent)
    :ResizeablePicture(parent) {
    flapping_timer = new QTimer();
    connect(flapping_timer, &QTimer::timeout, this, &FlappyBird::flapping);
    is_flapping = true;
    flapping_timer->start(200);
}

void FlappyBird::setType(int type) {
    if (type >=1 && type <= 2) this->type = type;
}

void FlappyBird::flapping() {
    std::string path = ":/resources/image/bird" + std::to_string(type) + "_" + std::to_string(state) + ".png";
    setPixmap(QPixmap(path.c_str()));
    ++state;
    if (state > 2) state = 0;
}


void FlappyBird::setSpeed(double speed) {
    this->speed = speed;
}

double FlappyBird::getSpeed() const{
    return speed;
}

void FlappyBird::toggleFlapping() {
    if (is_flapping) flapping_timer->stop();
    else flapping_timer->start(200);
    is_flapping = !is_flapping;
}
