/**
 * @file 玩家类
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class player : public QObject
{
    Q_OBJECT
public:
    explicit player(QObject *parent = nullptr);

signals:
};

#endif // PLAYER_H
