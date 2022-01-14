#include <QSound>
#include "Brick.h"
#include "Mario.h"
#include "BrickDebris.h"

Brick::Brick(QPoint position) : Inert()
{
	// set texture and position
	setPixmap(QPixmap(loadTexture(":/graphics/brick.bmp")));
	setPos(position);

	hitted = false;
	broken = false;
	hit_counter = 0;
}

// manage collisions with Mario
void Brick::advance()
{
	// do nothing if brick is not visible
	if(this->isVisible() == 0)
		return;

	// hit by Mario: move upwards and downwards
	if(hitted)
	{
		if(hit_counter < 10)
			setY(y()-1);
		else if(hit_counter < 20)
			setY(y()+1);
		
		hit_counter++;

		if(hit_counter >= 20)
		{
			hitted = false;
			hit_counter = 0;
		}
	}
	else if(broken)
	{
		setVisible(false);

		// spawn debris
		new BrickDebris(QPoint(x(),                  y()-15), LEFT);
		new BrickDebris(QPoint(x()+pixmap().width(), y()-15), RIGHT);
		new BrickDebris(QPoint(x()-5,                  y()-5), LEFT);
		new BrickDebris(QPoint(x()+pixmap().width()+5, y()-5), RIGHT);
	}
}

void Brick::hit(Object *what, Direction fromDir)
{
	// hit by Mario from bottom
	Mario* mario = dynamic_cast<Mario*>(what);
	if(mario && fromDir == DOWN)
	{
		if(mario->isBig())
		{
			QSound::play(":/sounds/block-break.wav");
			broken = true;
		}
		else
		{
			QSound::play(":/sounds/block-hit.wav");
			hitted = true;
			hit_counter = 0;
		}
	}
}
