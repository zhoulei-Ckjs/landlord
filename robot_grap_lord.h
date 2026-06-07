#ifndef ROBOT_GRAP_LORD_H
#define ROBOT_GRAP_LORD_H

#include <QThread>
#include "player.h"

class RobotGrapLord : public QThread
{
    Q_OBJECT
public:
    explicit RobotGrapLord(Player* player, QObject *parent = nullptr);

signals:
private:
    Player* player_;
};

#endif // ROBOT_GRAP_LORD_H
