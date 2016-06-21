#ifndef CARD_HH
#define CARD_HH

typedef unsigned short int RANK;

class Cardproxy;

enum SUITE
{
    ZERO,
    CLUB,
    DIAMOND,
    HEART,
    SPADE
};

class Card
{
public:
    Card(SUITE suite, RANK rank);
    ~Card();

    bool operator<(const Card& card) const
        {
        return card.rank()<m_rank;
        }

    RANK rank() const           {return m_rank;}
    SUITE suite() const         {return m_suite;}

    void set_proxy(Cardproxy *c){m_proxy = c;}
    Cardproxy *get_proxy()      {return m_proxy;}

    bool selected();

private:
    RANK    m_rank;
    SUITE   m_suite;

    Cardproxy *m_proxy;
};

SUITE GetSuite(unsigned short int i);

#endif // CARD_HH
