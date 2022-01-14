#include "turtle_back.h"

#include"Mario.h"
Turtle_back::Turtle_back(QPoint position, Direction direction)
{
    // set textures
    texture_Turtle_back= QPixmap(loadTexture(":/graphics/turtle-turtleback-0.png"));
    //texture_dead = QPixmap(loadTexture(":/graphics/goomba-dead.png"));

    // set direction
    dir = direction;

    // set texture and correct y-coordinate w.r.t. texture height
    setPixmap(texture_Turtle_back);
    setPos(position - QPoint(0, pixmap().height()));

    ////////////////////////
    falling=true;
    dying=true;
    death_duration   = 200;
    ///////////////////////
}

void Turtle_back::animate()
{
       // setPixmap(texture_ball[(walk_counter++/walk_div)%2]);
}

void Turtle_back::hit(Object *what, Direction fromDir)
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
            setDirection(inverse(dir));
    }
}
