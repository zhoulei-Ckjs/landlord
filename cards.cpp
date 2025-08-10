#include "cards.h"

#include <QRandomGenerator>

Cards::Cards() {}

void Cards::Add(const Card &card)
{
    cards_.insert(card);
}

void Cards::Clear()
{
    cards_.clear();
}

Card Cards::TakeRandomCard()
{
    int num = QRandomGenerator::global()->bounded(cards_.size());
    QSet<Card>::const_iterator it = cards_.constBegin();

    for(int i = 0; i < num; i++)
        ++it;

    Card card = *it;
    cards_.erase(it);
    return card;
}
