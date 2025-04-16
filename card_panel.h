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

signals:
};

#endif // CARD_PANEL_H
