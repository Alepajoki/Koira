#include "game.hh"
#include "deck.hh"
#include "cardproxy.hh"
#include "player.hh"
#include "mainwindow.hh"

#include <algorithm>
#include <assert.h>

Game::Game(MainWindow *window) : m_window(window)
{
m_deck = new Deck();
m_deck->shuffle();
m_window->set_game(this);
}


void Game::add_player(Player *player)
{
m_players.push_back(player);
}

void Game::run_phase1()
{
init_phase1();
while(!hands_empty())
    play_turn_phase1();
}

void Game::run_phase2()
{
init_phase2();
Player *starter = m_master.first;
while(!loser())
    starter = play_turn_phase2(starter);
Player *loserp = loser();
loserp->hand_empty();
}

void Game::init_phase1()
{
for(auto It=m_players.begin(); It!=m_players.end(); ++It)
    {
    for(unsigned short int i = 0; i < 3; ++i)
        {
        Card *card = (*It)->pick_card(m_deck);
        m_window->add_card(*It,card);
        }
    }
}

void Game::init_phase2()
{
m_master.first->set_stored(m_master.second);
for(auto It=m_players.begin(); It!=m_players.end(); ++It)
    if((*It)->store_empty())
        m_polloplayers.push_back(*It);
std::remove_if(m_players.begin(),m_players.end(),[](Player *p){return p->store_empty();});
}


void Game::play_turn_phase1()
{
Player *getter = play_round_phase1(m_players);
getter->set_stored(m_table);
m_table.clear();
}


Player *Game::play_round_phase1(std::vector<Player *> &players)
{
if(players.size()==1)
    return *players.begin();
TABLE localtable;
for(auto It=players.begin(); It!=players.end(); ++It)
    {
    Card *card = (*It)->play_card(PHASE1,this);
    if(m_deck->master())
        m_master = std::make_pair((*It),m_deck->pop_top());
    Card *pickedcard = (*It)->pick_card(m_deck);
    m_window->add_card(*It,pickedcard);
    if(card)
        {
        m_table.push_back(std::make_pair((*It),card));
        localtable.push_back(std::make_pair((*It),card));
        }
    }
std::vector<Player *> maxs;
RANK max = 0;
for(auto It=localtable.begin(); It!=localtable.end(); ++It)
    {
    Player *p = (*It).first;
    Card *i = (*It).second;
    if(maxs.empty())
        {
        maxs.push_back(p);
        max = i->rank();
        continue;
        }
    if(i->rank() > max)
        {
        maxs.clear();
        maxs.push_back(p);
        continue;
        }
    if(i->rank() == max)
        {
        maxs.push_back(p);
        }
    }
return play_round_phase1(maxs);
}


bool Game::hands_empty()
{
bool ret = true;
for(auto It=m_players.begin(); It!=m_players.end(); ++It)
    if(!(*It)->hand_empty())
        {
        ret = false;
        break;
        }
return ret;
}

Player *Game::loser()
{
Player *loser = nullptr;
for(auto It=m_players.begin(); It!=m_players.end(); ++It)
    {
    if(!loser && !(*It)->store_empty())
        {
        loser = *It;
        continue;
        }
    else if(loser && !(*It)->store_empty())
        {
        loser = nullptr;
        break;
        }
    }
return loser;
}


Player *Game::play_turn_phase2(Player *starter)
{
Player *i = starter;
if(i->store_empty())
    i = next(i);
while(m_table.size()<m_players.size())
    {
    if(i)
        {
        Card *card = i->play_card(PHASE2,this);
        if(card)
            m_table.push_back(std::make_pair(i,card));
        else
            {
            i->set_stored(m_table.back().second);
            m_table.pop_back();
            }
        i = next(i);
        }
    else
        i=m_players.front();
    }
Player *destroyer = m_table.back().first;
m_table.clear();
return destroyer;
}


void Game::win_player(Player *player)
{
auto It=m_players.begin();
while(It!=m_players.end())
    {
    if(*It==player)
        break;
    ++It;
    }
if(It!=m_players.end())
    m_players.erase(It);
m_wonplayers.push_back(player);
}


Player *Game::next(Player *player)
{
Player *next = nullptr;
for(auto It=m_players.begin(); It!=m_players.end(); ++It)
    {
    if((*It)==player && (*It)!=m_players.back())
        {
        ++It;
        next = *It;
        break;
        }
    else if((*It)==player && (*It)==m_players.back())
        {
        next = m_players.front();
        break;
        }
    }
return next;
}
