#pragma once

#include <QGraphicsScene>
#include <string>

#include "Mario.h"

class LevelManager
{
    public:

        // load all items from the given level in the given scene
        // also returns the Mario object
        static Mario* load(QString level_name, QGraphicsScene * scene);
};
