#include "player.hh"
#include "game.hh"
#include "deck.hh"
#include "mainwindow.hh"

#include <assert.h>
#include <QEventLoop>
#include <QPushButton>

Player::Player(unsigned short id) : m_id(id)
{
}

Player::~Player()
{

}

Card *Player::pick_card(Deck *deck)
{
if(deck->empty())
    return nullptr;
Card *card = deck->pop_top();
m_hand.push_back(card);
return card;
}


Card *Player::play_card(unsigned short int phase, Game *game)
{
switch(phase)
    {
    case PHASE1:
        {
        if(m_hand.empty())
            return nullptr;
        Card *card = nullptr;
        if(this==game->get_user())
            {
            QEventLoop loop;
            QPushButton *hitbutton = game->get_window()->get_hitbutton();
            loop.connect(hitbutton,SIGNAL(clicked(bool)),&loop,SLOT(quit()));
            loop.exec();
            card = get_selected_card(phase);
            }
        else
            card = m_hand.back();
        del_handcard(card);
        game->get_window()->del_card(this,card);
        return card;
        }
    case PHASE2:
        {
        std::vector<std::pair<Player *,Card *>> *table = game->get_table();
        Card *hit = nullptr;
        SUITE mastersuite = game->get_mastersuite();
        if(!table->empty())
            {
            Card *last = table->back().second;
            hit = find_hit(last,mastersuite);
            }
        else
            hit = random_smallest_store(mastersuite);
        if(hit)
            del_stored(hit);
        if(store_empty())
            game->win_player(this);
        return hit;
        }
    }
return nullptr;
}


void Player::set_stored(std::vector<std::pair<Player *, Card *> > &table)
{
for(auto It=table.begin(); It!=table.end(); ++It)
    m_store[(*It).second->suite()].insert((*It).second);
}


void Player::set_stored(Card *card)
{
m_store[card->suite()].insert(card);
}


Card *Player::find_hit(Card *last, SUITE mastersuite)
{
Card *hit = nullptr;
if(m_store.find(last->suite())!=m_store.end())
    for(auto It=m_store[last->suite()].begin(); It!=m_store[last->suite()].end(); ++It)
        if((*It)->rank() > last->rank())
            {
            hit = *It;
            break;
            }
if(hit)
    return hit;

if(last->suite()!=mastersuite && m_store.find(mastersuite)!=m_store.end())
    return *m_store[mastersuite].begin();

return nullptr;
}


Card *Player::random_smallest_store(SUITE mastersuite)
{
Card *random = nullptr;
for(auto It=m_store.begin(); It!=m_store.end(); ++It)
    {
    if((*It).first!=mastersuite)
        {
        random = *(*It).second.begin();
        break;
        }
    }
if(!random && m_store.find(mastersuite)!=m_store.end())
    random = *m_store[mastersuite].begin();
return random;
}


void Player::del_stored(Card *card)
{
auto It=m_store[card->suite()].begin();
for(; It!=m_store[card->suite()].end(); ++It)
    if(*It==card)
        break;
m_store[card->suite()].erase(It);
if(m_store[card->suite()].empty())
    {
    auto It2=m_store.begin();
    for(; It2!=m_store.end(); ++It2)
        if((*It2).first==card->suite())
            break;
    m_store.erase(It2);
    }
}


Card *Player::get_selected_card(unsigned short int phase)
{
Card *card = nullptr;
switch(phase)
    {
    case PHASE1:
    for(auto It=m_hand.begin(); It!=m_hand.end(); ++It)
        if((*It)->selected())
            card = *It;
    break;

    case PHASE2:
    break;
    }
return card;
}


void Player::del_handcard(Card *card)
{
for(auto It=m_hand.begin(); It!=m_hand.end(); ++It)
    if(*It==card)
    {
        m_hand.erase(It);
        break;
    }
}
