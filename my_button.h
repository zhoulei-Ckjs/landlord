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
    void SetImage(QString normal, QString hover, QString pressed);

    signals:

protected:
    /**
     * @brief 鼠标按下事件
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief 鼠标释放事件
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief 鼠标进入事件
     */
    void enterEvent(QEnterEvent *event);

    /**
     * @brief 鼠标离开事件
     */
    void leaveEvent(QEvent *event);

    /**
     * @brief 重写绘画事件
     */
    void paintEvent(QPaintEvent* e);

private:
    QPixmap current_picture_;           ///< 当前图片
    QString normal_, hover_, pressed_;  ///< 鼠标在正常、悬浮及按下时的图片
};

#endif // MY_BUTTON_H
