/**
 * @file 主窗口类
 */

#ifndef GAME_PANEL_H
#define GAME_PANEL_H

#include <QMainWindow>

#include "card_panel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GamePanel;
}
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();

    /**
     * @brief
     */
    void InitGameScene();

    /**
     * @brief 切割并存储图片
     */
    void InitCardMap();

protected:
    /**
     * @brief 游戏主窗口绘图事件
     */
    void paintEvent(QPaintEvent* e);

private:
    Ui::GamePanel *ui;

    QPixmap background_image_;          ///< 游戏主窗口背景图片
    QPixmap card_back_image_;           ///< 扑克牌的背面
    QSize card_size_;                   ///< 每张卡牌的大小
    CardPanel* base_card_;              ///< 发牌区中间的扑克牌
    QPoint base_card_pos_;              ///< 发牌区中间的扑克牌位置
    QVector<CardPanel*> last_3_cards_;  ///< 最后三张扑克牌
};
#endif // GAME_PANEL_H
