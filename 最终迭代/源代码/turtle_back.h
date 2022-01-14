#ifndef TURTLE_BACK_H
#define TURTLE_BACK_H

#include"Enemy.h"
class Turtle_back: public Enemy
{

protected:

    // textures
    QPixmap texture_Turtle_back;					// walking animation (2 textures)
    //QPixmap texture_dead;

    // animation divisors (inversely proportional to animation speed)
    static const int walk_div    = 10;			// walking animation

public:

    Turtle_back(QPoint position, Direction direction = RIGHT);

    // pure virtual methods that must be implemented
    virtual std::string name(){ return "Turtle_back";}
    virtual void animate();
    virtual void hit(Object *what, Direction fromDir);

    // hurt
    virtual void hurt(){};
};


#endif // TURTLE_BACK_H
