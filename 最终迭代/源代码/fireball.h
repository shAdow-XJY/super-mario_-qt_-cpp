#ifndef FIREBALL_H
#define FIREBALL_H

#include "Entity.h"

class Fireball : public Entity
{

protected:

    // textures
    QPixmap texture_ball[4];					// walking animation (2 textures)
    //QPixmap texture_dead;

    // animation divisors (inversely proportional to animation speed)
    static const int walk_div    = 10;			// walking animation

public:

    Fireball(QPoint position, Direction direction = RIGHT);

    // pure virtual methods that must be implemented
    virtual std::string name(){ return "Fireball";}
    virtual void animate();
    virtual void hit(Object *what, Direction fromDir);

    // hurt
    virtual void hurt(){};
};

#endif // FIREBALL_H
