#pragma once

#include "Inert.h"

class Terrain : public Inert
{
	public:

		Terrain(QRect rect);

        // pure virtual methods that must be implemented
        virtual std::string name() { return "Terrain"; }
        virtual void hit(Object *what, Direction fromDir) { /* do nothing */ }
};
