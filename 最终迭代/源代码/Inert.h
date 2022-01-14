#pragma once

#include "Object.h"

// Inert objects are not animated and do not move
// (a few exceptions may apply, so we keep methods virtual)
class Inert : public Object
{
    public:

		Inert();

        // inherited methods
        virtual std::string name()     = 0;
        virtual void animate()         { /* do nothing */ }
        virtual void advance()         { /* do nothing */ }
        virtual void solveCollisions() { /* do nothing */ }
        virtual void hit(Object *what, Direction fromDir) = 0;
};
