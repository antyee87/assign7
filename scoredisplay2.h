#ifndef SCOREDISPLAY2_H
#define SCOREDISPLAY2_H

#include <QWidget>

namespace Ui {
class ScoreDisplay2;
}

class ScoreDisplay2 : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreDisplay2(QWidget *parent = nullptr);
    ~ScoreDisplay2();
    void setScore(int score);

private:
    Ui::ScoreDisplay2 *ui;
};

#endif // SCOREDISPLAY2_H
