#pragma once

#include "Entity.h"

// Enemy objects are entities that can hurt Mario
// and that Mario can hurt
class Enemy : public Entity
{
	protected:

		bool hurtable;		// whether it can be hurt by Mario's feet

	public:

		Enemy();

		// getters
		bool isHurtable(){return hurtable;}

		// pure virtual methods that must be implemented
		virtual std::string name() = 0;
		virtual void animate()     = 0;
		virtual void hit(Object *what, Direction fromDir) = 0;

		// hurt
		virtual void hurt() = 0;
};