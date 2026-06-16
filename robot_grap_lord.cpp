#include "robot_grap_lord.h"

RobotGrapLord::RobotGrapLord(Player* player, QObject *parent)
    : QThread{parent}
{
    player_ = player;
}

void RobotGrapLord::run()
{
    msleep(2000);
    player_->ThinkCallLord();
}
