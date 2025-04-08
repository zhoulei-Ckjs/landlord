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

    /**
     * @brief 设置图片
     * @param normal 正常情况下的图片
     */
    void SetImage(QString normal);

    signals:

protected:
    /**
     * @brief 重写绘画事件
     */
    void paintEvent(QPaintEvent* e);

private:
    QPixmap current_picture_;           ///< 当前图片
};

#endif // MY_BUTTON_H
