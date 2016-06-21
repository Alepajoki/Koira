#ifndef TABLE_HH
#define TABLE_HH

#include "player.hh"
#include "card.hh"

#include <map>

class Player;

class Table
{
public:
    Table();

    void clear()    {m_cards.clear();}

private:
    std::map<Player *,Card *> m_cards;
};

#endif // TABLE_HH
