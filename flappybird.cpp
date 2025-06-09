#include "flappybird.h"

#include <string>
#include <QPixmap>

FlappyBird::FlappyBird(QWidget* parent)
    :ResizeablePicture(parent) {
    flapping_timer = new QTimer();
    connect(flapping_timer, &QTimer::timeout, this, &FlappyBird::flapping);
    flapping_timer->start(200);
}

void FlappyBird::setType(int type) {
    if (type >=1 && type <= 2) this->type = type;
}

void FlappyBird::flapping() {
    std::string path = ":/resources/image/bird" + std::to_string(type) + "_" + std::to_string(state) + ".png";
    QPixmap original = QPixmap(path.c_str());
    QTransform transform;
    transform.rotate(rotation);
    QPixmap rotated = original.transformed(transform, Qt::SmoothTransformation);
    setPixmap(rotated);
    resize(rotated.size());
    ++state;
    if (state > 2) state = 0;
}

void FlappyBird::setRotation(double rotation) {
    this->rotation = rotation;
}

double FlappyBird::getRotation() const{
    return rotation;
}

void FlappyBird::setSpeed(double speed) {
    this->speed = speed;
}

double FlappyBird::getSpeed() const{
    return speed;
}
