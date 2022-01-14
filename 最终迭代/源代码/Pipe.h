#pragma once

#include "Inert.h"
/////////////////////////////
enum dropable{
    NOT,         //Mario will not drop
    DROP         //Mario will drop
};
////////////////////////////

class Pipe : public Inert
{
    /////////////////
   protected:
       dropable ifdrop;
    //////////////////
    public:

        Pipe(QPoint position, int size,dropable ifdrop = NOT);

        // pure virtual methods that must be implemented
        virtual std::string name() { return "Pipe"; }
        virtual void hit(Object *what, Direction fromDir) ;
};
