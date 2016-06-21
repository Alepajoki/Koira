#ifndef DECK_HH
#define DECK_HH

#include <vector>

class Card;

class Deck
{
public:
    Deck();

    void shuffle();

    bool empty()    {return m_cards.empty();}
    bool master()   {return m_cards.size()==1;}
    Card *pop_top();

private:
    std::vector<Card *> m_cards;
};

#endif // DECK_HH
