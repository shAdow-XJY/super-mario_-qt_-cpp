#include "Box.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Flower.h"
#include "CoinSpawnable.h"
#include "Game.h"
#include <QSound>

Box::Box(QPoint position, visibility_t _visibility, spawnable_t _spawnable) : Inert()
{
	// load textures
	texture_cycle[0] = loadTexture(":/graphics/box-0.bmp");
	texture_cycle[1] = loadTexture(":/graphics/box-1.bmp");
	texture_cycle[2] = loadTexture(":/graphics/box-2.bmp");
	texture_used     = loadTexture(":/graphics/box-used.bmp");
	texture_brick	 = loadTexture(":/graphics/brick.bmp");

	// set properties
	used = false;
	hitted = false;
	hit_counter = 0;
	visibility = _visibility;
	spawnable = _spawnable;
	if(visibility == INVISIBLE)
		this->setOpacity(0.0);
	
	// set texture and position
	setPixmap(texture_cycle[0]);
	setPos(position);

	// be sure z-value is above mushroom's one
	setZValue(3);
}

void Box::animate()
{
	if(used)
		setPixmap(texture_used);
	else if(visibility == BRICKED)
		setPixmap(texture_brick);
	else
		setPixmap(texture_cycle[(hit_counter++/anim_div)%3]);
}

void Box::advance()
{
	// hit by Mario: move upwards and downwards
	if(hitted)
	{
		visibility = VISIBLE;
		setOpacity(1.0);

		if(hit_counter < 10)
			setY(y()-1);
		else if(hit_counter < 20)
			setY(y()+1);

		if(hit_counter > 20)
			hitted = false;

		hit_counter++;
	}
}

void Box::hit(Object *what, Direction fromDir)
{
	// hit by Mario from bottom
	Mario* mario = dynamic_cast<Mario*>(what);
	if(mario && fromDir == DOWN)
	{
		if(used)
			QSound::play(":/sounds/block-hit.wav");
		else
		{
			// spawn object
			if(spawnable == COIN)
				new CoinSpawnable(QPoint(x(), y()-20));
			else if(spawnable == POWERUP)
			{
				if(mario->isBig())
					new Flower(QPoint(x(), y()));
				else
					new Mushroom(QPoint(x(), y()));
			}
			else if(spawnable == LIFE)
				new Mushroom(QPoint(x(), y()), false);
            ////////////
            else if(spawnable == FLOWER)
                new Flower(QPoint(x(), y()));

			// set flags / counters
			hitted = true;
			used = true;
			hit_counter = 0;
		}
	}
}
