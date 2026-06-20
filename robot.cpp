#include <QDebug>
#include <random>

#include "robot.h"
#include "robot_grap_lord.h"

Robot::Robot(QObject *parent)
    : Player{parent}
{}

void Robot::PrepareCallLord()
{
    RobotGrapLord* sub_thread = new RobotGrapLord(this);
    connect(sub_thread, &RobotGrapLord::finished, this, [=](){
        qDebug() << "RobotGrapLord destoried, Robot name: " << this->GetName();
        sub_thread->deleteLater();
    });
    sub_thread->start();
}

void Robot::ThinkCallLord()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    int random_num = dis(gen);
    if(random_num < 70)
    {
        GrabLordBet(0);
    }
    else if(random_num < 80)
    {
        GrabLordBet(1);
    }
    else if(random_num < 90)
    {
        GrabLordBet(2);
    }
    else
    {
        GrabLordBet(3);
    }
}
