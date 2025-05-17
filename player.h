/**
 * @file 玩家类
 */

#ifndef PLAYER_H
#define PLAYER_H

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

signals:

protected :
    Player* next_ = nullptr;    ///< 当前玩家的下家
};

#endif // PLAYER_H
