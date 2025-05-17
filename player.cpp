#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{}

void Player::SetNextPlayer(Player *next)
{
    next_ = next;
}

Player *Player::GetNextPlayer()
{
    return next_;
}
