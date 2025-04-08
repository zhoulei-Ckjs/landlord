#include "my_button.h"

#include <QPainter>

MyButton::MyButton(QWidget *parent)
        : QPushButton{parent}
{}

void MyButton::SetImage(QString normal)
{
    current_picture_.load(normal);

    /// 重绘按钮
    update();
}

void MyButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(rect(), current_picture_);
}
