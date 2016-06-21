#include "deck.hh"
#include "card.hh"

#include <algorithm>
#include <chrono>

Deck::Deck()
{
for(unsigned short int i=1; i<5; ++i)
    for(RANK j=1; j<14; ++j)
        m_cards.push_back(new Card(GetSuite(i),j));
}

void Deck::shuffle()
{
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::shuffle(m_cards.begin(),m_cards.end(),std::default_random_engine(seed));
}

Card *Deck::pop_top()
{
Card *top = m_cards.back();
m_cards.pop_back();
return top;
}
