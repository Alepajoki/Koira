#include "mainwindow.hh"
#include <QApplication>

#include "card.hh"
#include "deck.hh"
#include "player.hh"
#include "game.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Game game(&w);
    game.add_player(new Player(0));
    game.add_player(new Player(1));
    game.add_player(new Player(2));
    game.add_player(new Player(3));

    game.run_phase1();
    //game.run_phase2();

    return a.exec();
}
