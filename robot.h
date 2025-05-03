/**
 * @brief 机器人类
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <Player.h>
#include <QObject>

class Robot : public Player
{
    Q_OBJECT
public:
    explicit Robot(QObject *parent = nullptr);

signals:
};

#endif // ROBOT_H
