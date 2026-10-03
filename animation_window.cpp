#include "animation_window.h"

#include <QPainter>

AnimationWindow::AnimationWindow(QWidget *parent)
    : QWidget{parent}
{}

void AnimationWindow::ShowBetScore(int bet)
{
    image_.load(":/res/img/game_pannel/animination_window/bet_score/score1.png");
    update();
}

void AnimationWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(0, 0, image_.width(), image_.height(), image_);
}
