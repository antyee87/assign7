#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <QWidget>

namespace Ui {
class ScoreDisplay;
}

class ScoreDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreDisplay(QWidget *parent = nullptr);
    ~ScoreDisplay();
    void setScore(int score);

private:
    Ui::ScoreDisplay *ui;
};

#endif // SCOREDISPLAY_H
