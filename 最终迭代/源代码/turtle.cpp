#include "turtle.h"
#include "Mario.h"

#include"turtle_back.h"
#include"fireball.h"
#include <QSound>

Turtle::Turtle(QPoint position, Direction direction)
{
    // set textures
    texture_walk[0] = QPixmap(loadTexture(":/graphics/turtle-walk-0.png"));
    texture_walk[1] = QPixmap(loadTexture(":/graphics/turtle-walk-1.png"));
    texture_dead = QPixmap(loadTexture(":/graphics/turtle-turtleback-1.png"));

    // set direction
    dir = direction;

    // set texture and correct y-coordinate w.r.t. texture height
    setPixmap(texture_walk[0]);
    setPos(position - QPoint(0, pixmap().height()));

    /////////////////////////
    death_duration   = 500;
    ///////////////////////
}

void Turtle::animate()
{
    if(dying || dead)
       setPixmap(texture_dead);
    else
    if(moving)
        setPixmap(texture_walk[(walk_counter++/walk_div)%2]);

    if(dir == RIGHT)
        setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

void Turtle::hit(Object *what, Direction fromDir)
{
    ///////////////////////////////////////
    // if hit by Frieball,  dies
    Fireball* fireball = dynamic_cast<Fireball*>(what);
    if(fireball)
    {
        fireball->die();
        QSound::play(":/sounds/stomp.wav");
        death_duration   = 0;
        die();
        //hurt();
        return;
    }
    Turtle_back* turtle_back = dynamic_cast<Turtle_back*>(what);
    if(turtle_back)
    {
        hurt();
        turtle_back->die();
        return;
    }

    if(fromDir==UP)
    {
        if(!dying)
        {
        hurt();
        return;
       }
        death_duration   = 0;
        die();
        int dy= texture_dead.height();
        new Turtle_back(QPoint(x(),y()+dy));
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
void Turtle::hurt()
{
    QSound::play(":/sounds/stomp.wav");
    //die();
    dying=true;
    // start death counter
    death_counter = 0;

    // cannot move
    moving = false;
}

