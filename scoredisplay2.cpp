#include "scoredisplay2.h"
#include "ui_scoredisplay2.h"

#include <QLabel>

ScoreDisplay2::ScoreDisplay2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScoreDisplay2)
{
    ui->setupUi(this);
}

ScoreDisplay2::~ScoreDisplay2()
{
    delete ui;
}

void ScoreDisplay2::setScore(int score) {
    std::string str_score = std::to_string(score);
    for (auto& widget : children()) {
        if (widget->property("isDigit").toBool()) widget->deleteLater();
    }
    for (int i = 0; i < str_score.length(); ++i) {
        QLabel* digit = new QLabel();
        digit->setProperty("isDigit", true);
        std::string path = std::string() + ":/resources/image/number_score_0" + str_score[i] + ".png";
        digit->setPixmap(QPixmap(path.c_str()));
        ui->horizontalLayout->addWidget(digit, 0, Qt::AlignRight | Qt::AlignVCenter);
    }
}
