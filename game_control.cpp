#include "game_control.h"

GameControl::GameControl(QObject *parent)
    : QObject{parent}
{}

void GameControl::PlayerInit()
{
    /// 对象初始化
    robot_left_ = new Robot(this);
    robot_right_ = new Robot(this);
    user_ = new UserPlayer(this);

    /// 指定当前玩家
    curr_player_ = user_;
}

Player *GameControl::GetCurrentPlayer()
{
    return curr_player_;
}
