#pragma once

#include "Enemy.h"

class Goomba : public Enemy
{
    protected:

		// textures
        QPixmap texture_walk[2];					// walking animation (2 textures)
        QPixmap texture_dead;

		// animation divisors (inversely proportional to animation speed)
		static const int walk_div    = 10;			// walking animation

    public:

        Goomba(QPoint position, Direction direction = RIGHT);

        // pure virtual methods that must be implemented
        virtual std::string name(){ return "Goomba";}
        virtual void animate();
        virtual void hit(Object *what, Direction fromDir);

		// hurt
		virtual void hurt();
};
