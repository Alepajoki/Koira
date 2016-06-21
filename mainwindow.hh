#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>

#define WINDOW_HEIGHT       1820
#define WINDOW_WIDTH        1080
#define PLAYERAREA_WIDTH    100
#define HITBUTTON_HEIGHT    50
#define HITBUTTON_WIDTH     100

class Player;
class Game;
class Card;
class Cardproxy;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void add_card(Player *player, Card *card);
    void del_card(Player *player, Card *card);
    void set_game(Game *g) {m_game = g;}

    void update_hit_button();
    QPushButton *get_hitbutton()  {return m_hitbutton;}

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QPushButton *m_hitbutton;
    Game *m_game;

    QRectF player1area;
    QRectF player2area;
    QRectF player3area;
    QRectF player4area;

    std::map<Player *, std::vector<Cardproxy *>> proxies;
};

#endif // MAINWINDOW_HH
