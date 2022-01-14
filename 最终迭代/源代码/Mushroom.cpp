#include "Mushroom.h"
#include "Mario.h"
#include <QSound>

Mushroom::Mushroom(QPoint position, bool _red) : Entity()
{
	// set texture and position
	red = _red;
	setPixmap(loadTexture(red ? ":/graphics/mushroom-red.png": ":/graphics/mushroom-green.png"));
	setPos(position);

	// set properties
	collectable = true;
	collidable = false;
	moving = true;
	dir = UP;
	falling = false;
	moving_speed = 1;
	falling_speed = 1;
	moving_speed_div = 6;
	slow = true;
	setZValue(2);
	spawned_position = position;
	death_duration = 0;

	// play mushroom sound
	QSound::play(":/sounds/mushroom-appear.wav");
}

void Mushroom::animate()
{
	// increase main animation counter (also used to slow down the entity in 'slow' mode)
	walk_counter++;

	// if mushroom fully emerges from spawn position, 
	// start moving right and become collidable
	if(y() == spawned_position.y()-pixmap().height())
	{
		collidable = true;
		falling = true;
		dir = RIGHT;
		moving_speed_div = 2;
	}
}

void Mushroom::hit(Object *what, Direction fromDir)
{
	// if hit by Mario, Mario eats mushroom and mushroom dies
	Mario* mario = dynamic_cast<Mario*>(what);
	if(mario)
	{
		mario->mushroomEat(red);
		die();
		return;
	}

	// if hit from its left or right side, it
	// has to move to the opposite direction w.r.t. the one
	// is he currently moving
	if(fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}