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
    void setType(int type);
    void setSpeed(double speed);
    double getSpeed() const;
    void toggleFlapping();

private:
    void flapping();
    QTimer* flapping_timer = nullptr;
    int type = 0, state = 0;
    double speed = 0;
    bool is_flapping;
};

#endif // FLAPPYBIRD_H
