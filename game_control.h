/**
 * @brief 游戏控制类
 */

#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include "Player.h"
#include "robot.h"
#include "user_player.h"
#include "card.h"
#include "cards.h"

#include <QObject>

class GameControl : public QObject
{
    Q_OBJECT
public:
    enum GameStatus
    {
        DISPATCH_CARD,
        CALLING_LORD
    };

    enum PlayerStatus
    {
        THINKING_FOR_CALL_LORD
    };

    explicit GameControl(QObject *parent = nullptr);

    /**
     * @brief InitAllCards 初始化扑克牌
     */
    void InitAllCards();

    /**
     * @brief OnGrabBet 处理叫地主
     * @param player 玩家
     * @param bet 分数
     */
    void OnGrabBet(Player* player, int bet);

    /**
     * @brief PlayerInit 初始化玩家
     */
    void PlayerInit();

    /**
     * @brief SetCurrentPlayer 设置当前玩家
     * @param player 当前玩家
     */
    void SetCurrentPlayer(Player* player);

    /**
     * @brief StartLordCard 准备叫地主
     */
    void StartLordCard();

    /**
     * @brief GetCurrentPlayer 获取当前玩家对象
     * @return 玩家
     */
    Player* GetCurrentPlayer();

    /**
     * @brief GetLeftRobot 得到玩家的实例对象
     * @return 玩家
     */
    Player* GetLeftRobot();
    Player* GetRightRobot();
    Player* GetUserPlayer();

    /**
     * @brief TakeOneCard 获取一张卡牌
     * @return 获取到的卡牌
     */
    Card TakeOneCard();

    /**
     * @brief GetSurplusCards 得到最后三张底牌
     * @return 卡牌
     */
    Cards GetSurplusCards();

signals:
    /**
     * @brief PlayerStatusChanged 玩家状态变化
     * @param player 玩家
     * @param status 状态
     */
    void PlayerStatusChanged(Player* player, PlayerStatus status);

private:
    Robot* robot_left_ = nullptr;       ///< 左侧机器人
    Robot* robot_right_ = nullptr;      ///< 右侧机器人
    UserPlayer* user_ = nullptr;        ///< 玩家
    Player* curr_player_ = nullptr;     ///< 当前玩家
    Cards all_cards_;                   ///< 所有扑克牌
};

#endif // GAME_CONTROL_H
