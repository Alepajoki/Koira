#include "cardproxy.hh"
#include "card.hh"
#include "mainwindow.hh"
#include "game.hh"

const QRectF cardrect = QRectF(0,0,CARD_WIDTH,CARD_HEIGHT);

Cardproxy::Cardproxy(Card *card, Game *game)
{
m_card = card;
m_game = game;
m_selectable = false;
m_selected = false;
m_card->set_proxy(this);
}

QRectF Cardproxy::boundingRect() const
{
    return cardrect;
}

void Cardproxy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
QPen pen(Qt::black,1);

QString s1 = QString::number(m_card->suite());
QString s2 = QString::number(m_card->rank());
QString s3 = s1+"_"+s2;

painter->setPen(pen);
painter->setBrush(QBrush(Qt::white));
painter->drawRect(cardrect);

pen.setWidth(3);
painter->setPen(pen);
painter->drawText(cardrect,s3);
}

void Cardproxy::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
if(selectable())
    {
    select(!selected());
    selected() ? setPos(this->x(),this->y()-20) : setPos(this->x(),this->y()+20);
    }
get_window()->update_hit_button();
}

MainWindow *Cardproxy::get_window()
{
return m_game->get_window();
}
