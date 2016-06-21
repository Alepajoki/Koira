#ifndef HAND_HH
#define HAND_HH

#include <vector>

#include "card.hh"
#include "deck.hh"

class Card;

class Hand
{
public:
    Hand();
    virtual ~Hand() {};

    void add(Card *card)    {m_cards.push_back(card);}

private:
    std::vector<Card *> m_cards;
};

#endif // HAND_HH
