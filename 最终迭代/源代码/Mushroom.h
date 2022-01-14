#pragma once

#include "Entity.h"

class Mushroom : public Entity
{
	protected:

		QPoint spawned_position;
		bool red;					// whether the mushroom is red (power up) or green (life up)
	
	public:

		Mushroom(QPoint position, bool _red = true);

		// inherited methods
		virtual std::string name() {return "Mushroom";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
};