#include "robot_grap_lord.h"

RobotGrapLord::RobotGrapLord(Player* player, QObject *parent)
    : QThread{parent}
{
    player_ = player;
}
