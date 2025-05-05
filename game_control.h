/**
 * @brief 游戏控制类
 */

#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include <QObject>

class GameControl : public QObject
{
    Q_OBJECT
public:
    explicit GameControl(QObject *parent = nullptr);

signals:

private:

};

#endif // GAME_CONTROL_H
