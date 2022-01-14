#pragma once

#include "Entity.h"

class CoinSpawnable : public Entity
{
	protected:

		QPoint spawned_position;
		QPixmap texture_cycle[4];

		// animation divisors (inversely proportional to animation speed)
		static const int anim_div = 6;	// main animation

	public:

		CoinSpawnable(QPoint position);

		// inherited methods
		virtual std::string name() {return "CoinSpawnable";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir){}
};