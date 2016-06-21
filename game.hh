#ifndef GAME_HH
#define GAME_HH

#include <set>
#include <vector>

#define PHASE1  0
#define PHASE2  1

class Player;
class Deck;
class MainWindow;
#include "card.hh"
class Card;

typedef std::vector<std::pair<Player *,Card *>> TABLE;

class Game
{
public:
    Game(MainWindow *window);

    void add_player(Player *player);
    void run_phase1();
    void run_phase2();

    std::vector<std::pair<Player *,Card *>> *get_table()    {return &m_table;}
    SUITE get_mastersuite()                                 {return m_master.second->suite();}

    Player *get_user()                                      {return m_players.front();}
    MainWindow *get_window()                                {return m_window;}
    void win_player(Player *);

private:
    void init_phase1();
    void init_phase2();
    void play_turn_phase1();
    Player *play_turn_phase2(Player *starter);
    Player *play_round_phase1(std::vector<Player *> &players);

    bool hands_empty();
    Player *loser();

    Player *next(Player *);

    std::vector<Player *> m_players;
    std::vector<Player *> m_wonplayers;
    std::vector<Player *> m_polloplayers;
    Deck *m_deck;
    TABLE m_table;
    std::pair<Player *,Card *> m_master;

    MainWindow *m_window;
};

#endif // GAME_HH
