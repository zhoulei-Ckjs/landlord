#include <QDebug>

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
