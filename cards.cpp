#include "cards.h"

#include <QRandomGenerator>

Cards::Cards() {}

Cards::Cards(const Card &card)
{
    Add(card);
}

void Cards::Add(const Card &card)
{
    cards_.insert(card);
}

int Cards::CardsCount()
{
    return cards_.size();
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
