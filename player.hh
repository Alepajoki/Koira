#ifndef PLAYER_HH
#define PLAYER_HH

#include <map>
#include <set>
#include <vector>

class Deck;
class Game;
#include "card.hh"
class Card;

class Player
{
public:
    Player(unsigned short int id);
    ~Player();

    Card *pick_card(Deck *deck);
    void del_handcard(Card *);
    Card *play_card(unsigned short int, Game *game=nullptr);
    bool hand_empty()               {return m_hand.empty();}
    int hand_size()                 {return m_hand.size();}
    bool store_empty()              {return m_store.empty();}
    std::vector<Card *> *get_hand() {return &m_hand;}

    void set_stored(std::vector<std::pair<Player *,Card *>> &);
    void set_stored(Card *);
    void del_stored(Card *);

    Card *get_selected_card(unsigned short int);

    unsigned short int id()         {return m_id;}

private:
    Card *find_hit(Card *last, SUITE mastersuite);
    Card *random_smallest_store(SUITE mastersuite);

    unsigned short int m_id;
    std::vector<Card *> m_hand;
    std::map<SUITE,std::set<Card *>> m_store;
};

#endif // PLAYER_HH
