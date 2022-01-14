#pragma once

#include "Entity.h"

class Flower : public Entity
{
	protected:

		// textures
		QPixmap texture_cycle[4];
		QPoint spawned_position;

		// animation divisors (inversely proportional to animation speed)
		static const int anim_div = 5;	// main animation

	public:

		Flower(QPoint position);

		// inherited methods
		virtual std::string name() {return "Flower";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
};