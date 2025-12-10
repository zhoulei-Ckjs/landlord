/**
 * @brief 卡牌窗口类
 */

#ifndef CARD_PANEL_H
#define CARD_PANEL_H

#include <QWidget>

class CardPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardPanel(QWidget *parent = nullptr);

    /**
     * @brief SetFrontSide 设置卡牌朝上面
     */
    void SetFrontSide(bool flag);

    /**
     * @brief 设置卡牌图片
     */
    void SetImage(const QPixmap& front, const QPixmap& back);

protected:
    /**
     * @brief 重写绘图事件
     */
    void paintEvent(QPaintEvent* event);

signals:

private:
    QPixmap front_;         ///< 卡牌前景图
    QPixmap back_;          ///< 卡牌背景图
    bool is_front_ = true;  ///< 是否显示为卡牌前景图
};

#endif // CARD_PANEL_H
