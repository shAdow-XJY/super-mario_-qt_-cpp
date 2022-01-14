#include "Goomba.h"
#include "Mario.h"

#include"turtle_back.h"
#include"fireball.h"
#include <QSound>

Goomba::Goomba(QPoint position, Direction direction)
{
	// set textures
    texture_walk[0] = QPixmap(loadTexture(":/graphics/goomba-0.png"));
    texture_walk[1] = QPixmap(loadTexture(":/graphics/goomba-1.png"));
    texture_dead = QPixmap(loadTexture(":/graphics/goomba-dead.png"));

	// set direction
	dir = direction;

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_walk[0]);
	setPos(position - QPoint(0, pixmap().height()));
}

void Goomba::animate()
{
	if(dying || dead)
		setPixmap(texture_dead);
    else if(moving)
        setPixmap(texture_walk[(walk_counter++/walk_div)%2]);
}

void Goomba::hit(Object *what, Direction fromDir)
{
    ///////////////////////////////////////
    // if hit by Frieball,  dies
    Fireball* fireball = dynamic_cast<Fireball*>(what);
     Turtle_back* turtle_back = dynamic_cast<Turtle_back*>(what);
    if(fireball)
    {
        QSound::play(":/sounds/stomp.wav");
        fireball->die();
        death_duration   = 0;
        hurt();
        return;
    }
    else if (turtle_back) {
        death_duration   = 0;
        hurt();
        return;
    }
    ////////////////////////////////

	// if hit from its left or right side, it
	// has to move to the opposite direction w.r.t. the one
	// is he currently moving
	if(fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}

// hurt
void Goomba::hurt()
{
	QSound::play(":/sounds/stomp.wav");
	die();
}

