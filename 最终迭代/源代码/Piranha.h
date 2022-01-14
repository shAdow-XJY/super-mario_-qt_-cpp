#ifndef PIRANHA_H
#define PIRANHA_H

#include"Enemy.h"
class Piranha: Enemy
{
protected:

    // textures
    QPixmap texture_cycle[2];
    QPoint spawned_position;

    // animation divisors (inversely proportional to animation speed)
    static const int anim_div = 25;	// main animation

public:
    Piranha(QPoint position);

    // inherited methods
    virtual std::string name() {return "Piranha";}
    virtual void animate();
    virtual void hit(Object *what, Direction fromDir);

    // hurt
    virtual void hurt(){/*nothing*/};
};

#endif // PIRANHA_H
