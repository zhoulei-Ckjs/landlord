/**
 * @file 玩家类
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "cards.h"

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    /**
     * @brief SetNextPlayer 设置当前玩家的下家
     * @param next 玩家
     */
    void SetNextPlayer(Player* next);

    /**
     * @brief GetNextPlayer 获取当前玩家的下家
     * @return 当前玩家的下家
     */
    Player* GetNextPlayer();

    /**
     * @brief GrabLordBet 叫地主，抢地主。
     * @param point 分数。
     */
    void GrabLordBet(int point);

    /**
     * @brief StoreDispatchCard 存储扑克牌
     * @param card 扑克牌
     */
    void StoreDispatchCard(const Card& card);

    /**
     * @brief GetCards 获取玩家的所有扑克牌
     * @return 玩家的所有卡牌
     */
    Cards GetCards();

signals:
    /**
     * @brief NotifyGrabLordBet 通知已经叫地主下注
     * @param player
     * @param bet
     */
    void NotifyGrabLordBet(Player* player, int bet);

protected :
    Player* next_ = nullptr;    ///< 当前玩家的下家
    Cards cards_;               ///< 存储多张扑克牌
};

#endif // PLAYER_H
