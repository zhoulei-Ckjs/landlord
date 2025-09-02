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
    explicit GameControl(QObject *parent = nullptr);

    /**
     * @brief PlayerInit 初始化玩家
     */
    void PlayerInit();

    /**
     * @brief InitAllCards 初始化扑克牌
     */
    void InitAllCards();

    /**
     * @brief SetCurrentPlayer 设置当前玩家
     * @param player 当前玩家
     */
    void SetCurrentPlayer(Player* player);

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

private:
    Robot* robot_left_ = nullptr;       ///< 左侧机器人
    Robot* robot_right_ = nullptr;      ///< 右侧机器人
    UserPlayer* user_ = nullptr;        ///< 玩家
    Player* curr_player_ = nullptr;     ///< 当前玩家
    Cards all_cards_;                   ///< 所有扑克牌
};

#endif // GAME_CONTROL_H
