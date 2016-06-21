#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include "cardproxy.hh"
#include "player.hh"
#include "game.hh"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player1area = QRectF(0,
                         WINDOW_HEIGHT-PLAYERAREA_WIDTH,
                         WINDOW_WIDTH,
                         PLAYERAREA_WIDTH);
    player2area = QRectF(0,
                         PLAYERAREA_WIDTH,
                         PLAYERAREA_WIDTH,
                         WINDOW_HEIGHT-2*PLAYERAREA_WIDTH);
    player3area = QRectF(0,
                         0,
                         WINDOW_WIDTH,
                         PLAYERAREA_WIDTH);
    player4area = QRectF(WINDOW_WIDTH-PLAYERAREA_WIDTH,
                         PLAYERAREA_WIDTH,
                         PLAYERAREA_WIDTH,
                         WINDOW_HEIGHT-2*PLAYERAREA_WIDTH);

    m_scene = new QGraphicsScene(ui->graphicsView);
    m_scene->setBackgroundBrush(QBrush(Qt::darkGreen));
    m_scene->setSceneRect(QRectF(0,0,WINDOW_WIDTH,WINDOW_HEIGHT));
    ui->graphicsView->setScene(m_scene);

    m_hitbutton = new QPushButton();
    m_hitbutton->setGeometry(WINDOW_WIDTH/2-HITBUTTON_WIDTH/2,
                             3*WINDOW_HEIGHT/4,
                             HITBUTTON_WIDTH,
                             HITBUTTON_HEIGHT);
    m_hitbutton->setText("Hit!");
    m_hitbutton->hide();
    m_scene->addWidget(m_hitbutton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_card(Player *player, Card *card)
{
Cardproxy *Cpxy = new Cardproxy(card,m_game);
unsigned short int id = player->id();
switch(id)
    {
    case 0:
        Cpxy->setPos(player1area.topLeft().x()+(player->hand_size()-1)*CARD_WIDTH,
                     player1area.topLeft().y());
        Cpxy->set_selectable(true);
        break;
    case 1:
        Cpxy->setPos(player2area.topRight().x(),
                     player2area.topRight().y()+(player->hand_size()-1)*CARD_WIDTH);
        Cpxy->setRotation(90);
        break;
    case 2:
        Cpxy->setPos(player3area.bottomRight().x()-(player->hand_size()-1)*CARD_WIDTH,
                     player3area.bottomRight().y());
        Cpxy->setRotation(180);
        break;
    case 3:
        Cpxy->setPos(player4area.bottomLeft().x(),
                     player4area.bottomLeft().y()-(player->hand_size()-1)*CARD_WIDTH);
        Cpxy->setRotation(270);
        break;
    }
proxies[player].push_back(Cpxy);
m_scene->addItem(Cpxy);
}

void MainWindow::del_card(Player *player, Card *card)
{
auto It=proxies.find(player);
if(It!=proxies.end())
    {
    for(auto It2=It->second.begin(); It2!=It->second.end(); ++It2)
        if((*It2)==card->get_proxy())
            {
            m_scene->removeItem(*It2);
            delete *It2;
            It->second.erase(It2);
            break;
            }
    }
}

void MainWindow::update_hit_button()
{
m_hitbutton->hide();
std::vector<Card *> *cards = m_game->get_user()->get_hand();
int count = 0;
for(auto It=cards->begin(); It!=cards->end(); ++It)
    if((*It)->get_proxy()->selected())
        count++;
if(count==1)
    m_hitbutton->show();
}
