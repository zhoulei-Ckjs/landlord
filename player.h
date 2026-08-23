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
    enum Direction
    {
        LEFT,
        RIGHT
    };

    enum Role
    {
        LORD,
        FARMER
    };

    enum Sex
    {
        MAN,
        WOMAN
    };

    explicit Player(QObject *parent = nullptr);
    explicit Player(QString name, QObject* parent = nullptr);

    /**
     * @brief GetCards 获取玩家的所有扑克牌
     * @return 玩家的所有卡牌
     */
    Cards GetCards();

    /**
     * @brief GrabLordBet 叫地主，抢地主。
     * @param point 分数。
     */
    void GrabLordBet(int point);

    /**
     * @brief 准备叫地主
     */
    virtual void PrepareCallLord();

    void SetDirection(Direction d);

    /**
     * @brief 玩家名字
     */
    void SetName(QString name);

    /**
     * @brief SetNextPlayer 设置当前玩家的下家
     * @param next 玩家
     */
    void SetNextPlayer(Player* next);

    void SetPrevPlayer(Player* prev);

    void SetRole(Role role);

    /**
     * @brief SetSex 设置玩家性别
     * @param sex 性别
     */
    void SetSex(Sex sex);

    Direction GetDirection();

    QString GetName();

    /**
     * @brief GetNextPlayer 获取当前玩家的下家
     * @return 当前玩家的下家
     */
    Player* GetNextPlayer();

    Player* GetPrevPlayer();

    Role GetRole();

    Sex GetSex();

    /**
     * @brief StoreDispatchCard 存储扑克牌
     * @param card 扑克牌
     */
    void StoreDispatchCard(const Card& card);

    virtual void ThinkCallLord();

signals:
    /**
     * @brief NotifyGrabLordBet 通知已经叫地主下注
     * @param player
     * @param bet
     */
    void NotifyGrabLordBet(Player* player, int bet);

protected :
    Cards cards_;               ///< 存储多张扑克牌
    Direction direction_;       ///< 玩家朝向方位
    QString name_;              ///< 玩家名字
    Player* next_ = nullptr;    ///< 当前玩家的下家
    Player* prev_ = nullptr;    ///< 当前玩家的上家。
    Role role_;                 ///< 玩家角色，地主、农民。
    Sex sex_;                   ///< 玩家性别
};

#endif // PLAYER_H
