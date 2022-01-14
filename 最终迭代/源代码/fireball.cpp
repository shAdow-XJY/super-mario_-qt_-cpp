#include "fireball.h"
#include <QSound>

#include"Mario.h"
Fireball::Fireball(QPoint position, Direction direction)
{
    // set textures
    texture_ball[0] = QPixmap(loadTexture(":/graphics/fireball-0.bmp"));
    texture_ball[1] = QPixmap(loadTexture(":/graphics/fireball-1.bmp"));
    texture_ball[2] = QPixmap(loadTexture(":/graphics/fireball-2.bmp"));
    texture_ball[3] = QPixmap(loadTexture(":/graphics/fireball-3.bmp"));
    //texture_dead = QPixmap(loadTexture(":/graphics/goomba-dead.png"));

    // set direction
    dir = direction;

    // set texture and correct y-coordinate w.r.t. texture height
    setPixmap(texture_ball[0]);
    setPos(position - QPoint(0, pixmap().height()));

    ////////////////////////
    falling=false;
    dying=true;
    death_duration   = 400;
    moving_speed*=1.5;
    ///////////////////////

    /// QSound::play
    QSound::play(":/sounds/stomp.wav");
}

void Fireball::animate()
{
        setPixmap(texture_ball[(walk_counter++/walk_div)%4]);
}

void Fireball::hit(Object *what, Direction fromDir)
{
    // if hit from its left or right side, it
    // has to move to the opposite direction w.r.t. the one
    // is he currently moving
    Mario *mario = dynamic_cast<Mario*>(what);
    if(mario)
    {
    }
    else if(fromDir == RIGHT || fromDir == LEFT)
    {
            death_duration   = 0;
    }
}



