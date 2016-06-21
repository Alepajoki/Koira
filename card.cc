#include "card.hh"
#include "cardproxy.hh"

#include <assert.h>

Card::Card(SUITE suite, RANK rank)
{
assert(rank>1 || rank<13);
m_rank = rank;
m_suite = suite;
}

Card::~Card()
{

}

SUITE GetSuite(unsigned short int i)
{
    switch(i)
    {
    case 1: return CLUB;
    case 2: return DIAMOND;
    case 3: return HEART;
    case 4: return SPADE;
    }
return ZERO;
}


bool Card::selected()
{
return m_proxy->selected();
}

