#include "card_panel.h"

#include <QPainter>

CardPanel::CardPanel(QWidget *parent)
    : QWidget{parent}
{}

void CardPanel::SetImage(const QPixmap &front, const QPixmap &back)
{
    front_ = front;
    back_ = back;

    /// 设置大小，只有设置有效的大小，才会触发paintEvent
    setFixedSize(front_.size());

    update();   ///< 触发绘画事件
}

void CardPanel::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    if(is_front_)
    {
        p.drawPixmap(rect(), front_);
    }
    else
    {
        p.drawPixmap(rect(), back_);
    }
}
