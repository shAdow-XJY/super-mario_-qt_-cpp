#pragma once

#include "Entity.h"

class BrickDebris : public Entity
{
	public:

		BrickDebris(QPoint position, Direction dir);

		// inherited methods
		virtual std::string name() {return "BrickDebris";}
		virtual void animate(){walk_counter++;}
		virtual void hit(Object *what, Direction fromDir){}
};