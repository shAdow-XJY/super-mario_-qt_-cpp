#include "Piranha.h"
#include"Mario.h"

Piranha::Piranha(QPoint position) : Enemy()
{
    // set texture and position
    texture_cycle[0] = loadTexture(":/graphics/piranha-0.png");
    texture_cycle[1] = loadTexture(":/graphics/piranha-1.png");

    setPixmap(texture_cycle[0]);
    setPos(position);

    // set properties
    collectable = true;
    collidable = true;
    dir = UP;
    moving = true;
    falling = false;
    moving_speed = 1;
    moving_speed_div = 6;
    slow = true;
    setZValue(2);
    spawned_position = position;
    death_duration = 0;


 //   QSound::play(":/sounds/mushroom-appear.wav");
}

void Piranha::animate()
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

    setPixmap(texture_cycle[(walk_counter/anim_div)%2]);
}

void Piranha::hit(Object *what, Direction fromDir)
{
    // if hit by Mario, Mario eats flower and flower dies
    Mario* mario = dynamic_cast<Mario*>(what);
    if(mario)
    {
      //  mario->hurt();
        return;
    }
}
