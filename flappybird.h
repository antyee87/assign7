#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include <QObject>
#include <QTimer>

#include "resizeablepicture.h"

class FlappyBird : public ResizeablePicture
{
    Q_OBJECT
public:
    FlappyBird(QWidget* parent);
    void flapping();
    void setType(int type);
    void setRotation(double rotation);
    double getRotation() const;
    void setSpeed(double speed);
    double getSpeed() const;

private:
    QTimer* flapping_timer = nullptr;
    int type = 0, state = 0;
    double rotation = 0;
    double speed = 0;
};

#endif // FLAPPYBIRD_H
