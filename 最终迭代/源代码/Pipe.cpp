#include "Pipe.h"
#include"Mario.h"
Pipe::Pipe(QPoint position, int size,dropable _ifdrop) : Inert()
{
	// set proper texture
	if(size == 0)
		setPixmap(QPixmap(loadTexture(":/graphics/pipe-small.png")));
	else if(size == 1)
		setPixmap(QPixmap(loadTexture(":/graphics/pipe-med.png")));
	else
		setPixmap(QPixmap(loadTexture(":/graphics/pipe-big.png")));

	// correct y-coordinate w.r.t. texture height
	setPos(position-QPoint(0, pixmap().height()));

    //////////////////////////////////////////////
    ifdrop=_ifdrop;
    /////////////////////////////////////////////
}

void Pipe::hit(Object *what, Direction fromDir)
{
    Mario* mario=dynamic_cast<Mario*>(what);
    if(mario&&fromDir==UP)
    {
        if(ifdrop==DROP)
        {
            mario->setpipe1(true);
            setZValue(4);
        }
    }
}
