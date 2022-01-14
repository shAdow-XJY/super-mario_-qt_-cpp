#include "CoinSpawnable.h"
#include <QSound>

CoinSpawnable::CoinSpawnable(QPoint position) : Entity()
{
	spawned_position = position;

	// load textures
    texture_cycle[0] = loadTexture(":/graphics/coin-0.png");
    texture_cycle[1] = loadTexture(":/graphics/coin-1.png");
    texture_cycle[2] = loadTexture(":/graphics/coin-2.png");
    texture_cycle[3] = loadTexture(":/graphics/coin-3.png");

	// set texture and position
	setPixmap(texture_cycle[0]);
	setPos(position);

	// set properties
	collidable = false;
	moving = false;
	falling = false;
	jumping_speed = 1;
	falling_speed = 1;
	death_duration = 0;
	setZValue(10);

	// jump
	startJumping();

	// play coin sound
	QSound::play(":/sounds/coin.wav");
}


void CoinSpawnable::animate()
{
	// if fallen below spawned (original) position, die
	if(falling && y() >= spawned_position.y())
		die();
	// otherwise continue animation
	else
		setPixmap(texture_cycle[(walk_counter++/anim_div)%3]);
}
