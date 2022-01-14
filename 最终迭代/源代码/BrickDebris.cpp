#include <QSound>
#include "BrickDebris.h"

BrickDebris::BrickDebris(QPoint position, Direction dir) : Entity()
{
	// set texture and position
	setPixmap(QPixmap(loadTexture(":/graphics/brick-debris.bmp")));
	setPos(position);

	// debris are not collidable
	collidable = false;

	// debris are always moving horizontally (slowly)
	moving = true;
	setDirection(dir);
	slow = true;

	// debris are overlaid on top of all other objects
	setZValue(10);

	// initially, debris are not falling
	falling = false;

	// once they are spawned, we make a small jump with random
	// duration so as to create the feeling of a true break
	jumping_duration = rand()%15;
	startJumping();
}