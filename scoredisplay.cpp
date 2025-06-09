#include "scoredisplay.h"
#include "ui_scoredisplay.h"

#include <string>

#include <QLabel>
#include <QPixmap>

ScoreDisplay::ScoreDisplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScoreDisplay)
{
    ui->setupUi(this);

}

ScoreDisplay::~ScoreDisplay()
{
    delete ui;
}

void ScoreDisplay::setScore(int score) {
    std::string str_score = std::to_string(score);
    for (auto& widget : children()) {
        if (widget->property("isDigit").toBool()) widget->deleteLater();
    }
    for (int i = 0; i < str_score.length(); ++i) {
        QLabel* digit = new QLabel();
        digit->setProperty("isDigit", true);
        std::string path = ":/resources/image/font_0" + std::to_string(str_score[i]) + ".png";
        digit->setPixmap(QPixmap(path.c_str()));
        ui->horizontalLayout->addWidget(digit, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    }
}
