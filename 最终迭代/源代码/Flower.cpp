#include "Flower.h"
#include "Mario.h"
#include <QSound>

Flower::Flower(QPoint position) : Entity()
{
	// set texture and position
	texture_cycle[0] = loadTexture(":/graphics/flower-0.bmp");
	texture_cycle[1] = loadTexture(":/graphics/flower-1.bmp");
	texture_cycle[2] = loadTexture(":/graphics/flower-2.bmp");
	texture_cycle[3] = loadTexture(":/graphics/flower-3.bmp");
	setPixmap(texture_cycle[0]);
	setPos(position);

	// set properties
	collectable = true;
	collidable = false;
	dir = UP;
	moving = true;
	falling = false;
	moving_speed = 1;
	moving_speed_div = 6;
	slow = true;
	setZValue(2);
	spawned_position = position;
	death_duration = 0;

	// play mushroom sound
	QSound::play(":/sounds/mushroom-appear.wav");
}

void Flower::animate()
{
	// increase main animation counter (also used to slow down the entity in 'slow' mode)
	walk_counter++;

	// if flower fully emerges from spawn position, 
	// fix its position (moving = false)
	if(y() == spawned_position.y()-pixmap().height())
	{
		collidable = true;
		moving = false;
	}

	setPixmap(texture_cycle[(walk_counter/anim_div)%4]);
}

void Flower::hit(Object *what, Direction fromDir)
{
	// if hit by Mario, Mario eats flower and flower dies
	Mario* mario = dynamic_cast<Mario*>(what);
	if(mario)
	{
		mario->flowerEat();
		die();
		return;
	}
}