#ifndef CASTLE_H
#define CASTLE_H

#include "Inert.h"
class Castle: public Inert
{
public:
        Castle(QPoint position);

        // pure virtual methods that must be implemented
        virtual std::string name() { return "Castle"; }
        virtual void hit(Object *what, Direction fromDir);
};

#endif // CASTLE_H
