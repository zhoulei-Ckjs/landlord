#include "my_button.h"

#include <QMouseEvent>
#include <QPainter>

MyButton::MyButton(QWidget *parent)
        : QPushButton{parent}
{}

void MyButton::SetImage(QString normal, QString hover, QString pressed)
{
    normal_ = normal;
    hover_ = hover;
    pressed_ = pressed;
    current_picture_.load(normal);

    /// 重绘按钮
    update();
}

void MyButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        current_picture_.load(pressed_);

        /// 重绘按钮
        update();
    }
    QPushButton::mousePressEvent(event);
}

void MyButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        current_picture_.load(normal_);

        /// 重绘按钮
        update();
    }
    QPushButton::mouseReleaseEvent(event);
}

void MyButton::enterEvent(QEnterEvent *event)
{
    current_picture_.load(hover_);

    /// 重绘按钮
    update();
}

void MyButton::leaveEvent(QEvent *event)
{
    current_picture_.load(normal_);

    /// 重绘按钮
    update();
}

void MyButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(rect(), current_picture_);
}
