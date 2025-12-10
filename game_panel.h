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
     * @brief CropImage 裁剪图片
     * @param pix 大图的pixmap
     * @param x 待裁剪的起始 x 位置
     * @param y 待裁剪的起始 y 位置
     * @param c 卡牌
     */
    void CropImage(QPixmap& pix, int x, int y, Card& c);

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
     * @brief StartDispatchCard 发牌
     */
    void StartDispatchCard();

    /**
     * @brief UpdatePlayerCards update player cards in window
     * @param player
     */
    void UpdatePlayerCards(Player* player);

    /**
     * @brief 发牌时的定时器处理动作
     */
    void OnDispatchCard();

    /**
     * @brief CardMoveStep 移动扑克牌
     * @param player 当前玩家
     * @param cur_pos 卡牌位置
     */
    void CardMoveStep(Player* player, int cur_pos);

    /**
     * @brief InitPlayerContext 初始化玩家窗口中上下文环境
     */
    void InitPlayerContext();

    /**
     * @brief InitButtonsGroup 初始化游戏按钮组
     */
    void InitButtonsGroup();

    /**
     * @brief DisposeCard 发牌给玩家
     * @param player 玩家
     * @param cards 卡牌
     */
    void DisposeCard(Player* player, const Cards& cards);

protected:
    /**
     * @brief 游戏主窗口绘图事件
     */
    void paintEvent(QPaintEvent* e);

private:
    enum CardAlign
    {
        HORIZONTAL,                     ///< 水平
        VERTICAL                        ///< 垂直
    };
    struct PlayerContext
    {
        QRect card_rect_;               ///< 玩家扑克牌显示区域
        CardAlign align_;               ///< 扑克牌对齐方式
        bool is_front_;                 ///< 扑克牌显示正面还是背面
    };

    Ui::GamePanel *ui;

    QPixmap background_image_;          ///< 游戏主窗口背景图片
    QPixmap card_back_image_;           ///< 扑克牌的背面
    QMap <Card, CardPanel*> card_map_;  ///< 卡牌与卡牌面板的映射
    QSize card_size_;                   ///< 每张卡牌的大小
    CardPanel* base_card_;              ///< 发牌区中间的扑克牌
    CardPanel* move_card_;              ///< 发牌时移动的牌
    QPoint base_card_pos_;              ///< 发牌区中间的扑克牌位置
    QVector<CardPanel*> last_3_cards_;  ///< 最后三张扑克牌
    QTimer* timer_;                     ///< 定时器，用于控制发牌时移动的牌
    QVector<Player*> player_list_;      ///< 玩家列表
    GameControl* game_ctl_;             ///< 游戏控制类
    QMap<Player*, PlayerContext> context_map_;  ///< 玩家上下文
};
#endif // GAME_PANEL_H
