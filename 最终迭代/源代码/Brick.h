#pragma once

#include "Inert.h"

class Brick : public Inert
{
	protected:

		bool hitted;				// whether the brick has been hit by Mario
		bool broken;				// whether the brick has been broken by Mario
		int  hit_counter;			// counts the number of frames since Mario hit

	public:

		Brick(QPoint position);

		// inherited methods
		virtual std::string name() {return "Brick";}
		virtual void advance();
		virtual void hit(Object *what, Direction fromDir);
};