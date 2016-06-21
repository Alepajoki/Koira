#ifndef CARDPROXY_HH
#define CARDPROXY_HH

#include <QGraphicsItem>
#include <QPainter>
#include <QMouseEvent>

#define CARD_HEIGHT 100
#define CARD_WIDTH  50

class Game;
class MainWindow;
class Card;

class Cardproxy : public QGraphicsObject
{
public:
    Cardproxy(Card *, Game *);

    virtual QRectF boundingRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void select(bool b)         {m_selected = b;}
    bool selected()             {return m_selected;}
    void set_selectable(bool b) {m_selectable = b;}
    bool selectable()           {return m_selectable;}

    MainWindow *get_window();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    Card *m_card;
    Game *m_game;
    bool m_selectable;
    bool m_selected;
};

#endif // CARDPROXY_HH
