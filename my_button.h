/**
 * @brief 自定义按钮类
 */

#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

    signals:
};

#endif // MY_BUTTON_H
