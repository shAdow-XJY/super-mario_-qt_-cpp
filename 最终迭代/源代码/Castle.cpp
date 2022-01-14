#include "Castle.h"
#include "Mario.h"
Castle::Castle(QPoint position): Inert()
{
    collidable=true;

    setPixmap(QPixmap(loadTexture(":/graphics/castle.png")));
    setPos(position-QPoint(0, pixmap().height()));

}
void Castle::hit(Object *what, Direction fromDir)
{
    Mario* mario = dynamic_cast<Mario*>(what);
    if(mario)
    {
        collidable=false;
        mario->castleAddress(x()+pixmap().width()/2,y()+pixmap().height()/2);
    }
}
