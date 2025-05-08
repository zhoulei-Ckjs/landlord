/**
 * @brief 玩家类
 */

#ifndef USER_PLAYER_H
#define USER_PLAYER_H

#include "player.h"

#include <QObject>

class UserPlayer : public Player
{
    Q_OBJECT
public:
    explicit UserPlayer(QObject *parent = nullptr);

signals:
};

#endif // USER_PLAYER_H
