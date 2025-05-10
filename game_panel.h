/**
 * @file 主窗口类
 */

#ifndef GAME_PANEL_H
#define GAME_PANEL_H

#include <Player.h>
#include <QMainWindow>

#include "card_panel.h"
#include "game_control.h"

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
     * @brief GameControlInit 初始化游戏控制类信息
     */
    void GameControlInit();

    /**
     * @brief 初始化游戏场景
     */
    void InitGameScene();

    /**
     * @brief 更新玩家得分
     */
    void UpdatePlayerScore();

    /**
     * @brief 切割并存储图片
     */
    void InitCardMap();

    /**
     * @brief 发牌时的定时器处理动作
     */
    void OnDispatchCard();

    /**
     * @brief CardMoveStep 移动扑克牌
     */
    void CardMoveStep(Player* player);

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
    CardPanel* move_card_;              ///< 发牌时移动的牌
    QPoint base_card_pos_;              ///< 发牌区中间的扑克牌位置
    QVector<CardPanel*> last_3_cards_;  ///< 最后三张扑克牌
    QTimer* timer_;                     ///< 定时器，用于控制发牌时移动的牌
    QVector<Player*> player_list_;      ///< 玩家列表
    GameControl* game_ctl_;             ///< 游戏控制类
};
#endif // GAME_PANEL_H
