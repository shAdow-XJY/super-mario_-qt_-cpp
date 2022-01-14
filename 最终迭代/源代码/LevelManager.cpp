#include "LevelManager.h"
#include <iostream>

#include "Background.h"
#include "Block.h"
#include "Box.h"
#include "Brick.h"
#include "Goomba.h"
#include "Mario.h"
#include "Pipe.h"
#include "Terrain.h"

#include"Castle.h"
#include"turtle.h"
#include"fireball.h"
#include "Piranha.h"
#include <QSoundEffect>

// load all items from the given level in the given scene
Mario* LevelManager::load(QString level_name, QGraphicsScene * scene)
{
    Mario* mario = 0;

    if(level_name == "World-1")
    {
        // set background color
        scene->setBackgroundBrush(QBrush(QColor(99,133,251)));

		// terrain level
        int terrain_level = 200;

		// welcome message
        new Background(QPoint(40,terrain_level-5.5*16), ":/graphics/welcome.png");

        // terrain   制造地形中间的空格空白处
        new Terrain(QRect(0,terrain_level,69*16,30));
        new Terrain(QRect(71*16,terrain_level,15*16,30));

        new Terrain(QRect(88*16,terrain_level,30*16,30));

        //Piranha
        new Piranha(QPoint(66*16, terrain_level));

        //Castle
       new Castle(QPoint(92*16,terrain_level));

        /*new Block(QPoint(75*16,terrain_level-9*16));
        new Block(QPoint(75*16,terrain_level-8*16));
        new Block(QPoint(75*16,terrain_level-7*16));
        new Block(QPoint(75*16,terrain_level-6*16));
        new Block(QPoint(75*16,terrain_level-5*16));
        new Block(QPoint(75*16,terrain_level-4*16));
        new Block(QPoint(75*16,terrain_level-3*16));
        new Block(QPoint(75*16,terrain_level-2*16));
        new Block(QPoint(75*16,terrain_level-1*16));
*/
		// left boundary
        new Terrain(QRect(-16, 0, 16, 200));

		// background hills/clouds/bushes
        new Background(QPoint(0,terrain_level),       ":/graphics/hill-big.png");
		//new Background(QPoint(8.5*16,terrain_level-8.5*16),  ":/graphics/cloud-small.png");
		new Background(QPoint(11.5*16,terrain_level), ":/graphics/bush-big.png");
		new Background(QPoint(16*16,terrain_level),   ":/graphics/hill-small.png");
        new Background(QPoint(19.5*16,terrain_level-9.6*16),  ":/graphics/cloud-small.png");
        new Background(QPoint(15*16,terrain_level-9.6*16),  ":/graphics/cloud-small.png");
		new Background(QPoint(23.5*16,terrain_level), ":/graphics/bush-small.png");
        new Background(QPoint(27.5*16,terrain_level-9.6*16),  ":/graphics/cloud-big.png");
        new Background(QPoint(36.5*16,terrain_level-9.6*16),  ":/graphics/cloud-med.png");
		new Background(QPoint(41.5*16,terrain_level), ":/graphics/bush-med.png");
		new Background(QPoint(48*16,terrain_level),   ":/graphics/hill-big.png");
		new Background(QPoint(59.5*16,terrain_level), ":/graphics/bush-big.png");
		new Background(QPoint(64*16,terrain_level),   ":/graphics/hill-small.png");





        // bricks / boxes        BOX没有说明内容默认为金币
        new Box(QPoint(16*16,terrain_level-4*16), VISIBLE,FLOWER);
		new Brick(QPoint(20*16,terrain_level-4*16));
        new Box(QPoint(21*16,terrain_level-4*16), VISIBLE, POWERUP);
		new Brick(QPoint(22*16,terrain_level-4*16));
		new Box(QPoint(23*16,terrain_level-4*16));
		new Brick(QPoint(24*16,terrain_level-4*16));
		new Box(QPoint(22*16,terrain_level-8*16));
        new Box(QPoint(65*16,terrain_level-5*16), INVISIBLE, POWERUP);

        //coin
        new Box(QPoint(12*16,terrain_level-4*16), VISIBLE);

        //turtle
        new Turtle(QPoint(20*16, terrain_level));
        new Turtle(QPoint(26*16, terrain_level));
        new Turtle(QPoint(42*16, terrain_level));
        new Turtle(QPoint(54*16, terrain_level));
        new Turtle(QPoint(90*16, terrain_level));
        new Turtle(QPoint(60*16, terrain_level));

		// pipes
        new Pipe(QPoint(18*16, terrain_level), 0,DROP);
		new Pipe(QPoint(28*16, terrain_level), 0);
		new Pipe(QPoint(38*16, terrain_level), 1);
		new Pipe(QPoint(46*16, terrain_level), 2);
		new Pipe(QPoint(57*16, terrain_level), 2);

        // Mario
        mario = new Mario(QPoint(16*2.5, terrain_level));


        // Goombas
        new Goomba(QPoint(60*16, terrain_level), LEFT);
		new Goomba(QPoint(40*16, terrain_level));
		new Goomba(QPoint(51*16, terrain_level));
        new Goomba(QPoint(52.5*16, terrain_level));

    }
    else  if(level_name == "World-2")
    {
        // set background color
        scene->setBackgroundBrush(QBrush(QColor(230,206,172)));

        // terrain level
        int terrain_level = 200;


        // terrain   制造地形中间的空格空白处
        new Terrain(QRect(0,terrain_level,30*16,30));
        new Terrain(QRect(32*16,terrain_level,60*16,30));
        //Castle
       new Castle(QPoint(55*16,terrain_level));


        // left boundary
        new Terrain(QRect(-16, 0, 16, 200));

        // LEVEL message
        new Background(QPoint(0,terrain_level), ":/graphics/WELCOME.ico");

        // background hills/clouds/bushes
        new Background(QPoint(0,terrain_level),       ":/graphics/hill-big.png");
        new Background(QPoint(8.5*16,terrain_level-8.5*16),  ":/graphics/cloud-small.png");
        new Background(QPoint(11.5*16,terrain_level), ":/graphics/bush-big.png");
        new Background(QPoint(16*16,terrain_level),   ":/graphics/hill-small.png");
        new Background(QPoint(19.5*16,terrain_level-6*16),  ":/graphics/cloud-small.png");
        new Background(QPoint(15*16,terrain_level-9.6*16),  ":/graphics/cloud-small.png");
        new Background(QPoint(23.5*16,terrain_level), ":/graphics/bush-small.png");
        new Background(QPoint(27.5*16,terrain_level-9.6*16),  ":/graphics/cloud-big.png");
        new Background(QPoint(36.5*16,terrain_level-9.6*16),  ":/graphics/cloud-med.png");
        new Background(QPoint(41.5*16,terrain_level), ":/graphics/bush-med.png");
        new Background(QPoint(48*16,terrain_level),   ":/graphics/hill-big.png");
        new Background(QPoint(59.5*16,terrain_level), ":/graphics/bush-big.png");
        new Background(QPoint(64*16,terrain_level),   ":/graphics/hill-small.png");


        // bricks / boxes        BOX没有说明内容默认为金币
        new Box(QPoint(16*16,terrain_level-4*16), VISIBLE,FLOWER);
        new Brick(QPoint(20*16,terrain_level-4*16));
        new Box(QPoint(21*16,terrain_level-4*16), VISIBLE, POWERUP);
        new Brick(QPoint(22*16,terrain_level-4*16));
        new Box(QPoint(23*16,terrain_level-4*16),BRICKED,POWERUP);
        new Brick(QPoint(23*16,terrain_level-4*16));
        new Box(QPoint(22*16,terrain_level-8*16));
        new Box(QPoint(65*16,terrain_level-5*16), INVISIBLE, POWERUP);
        new Box(QPoint(12*16,terrain_level-4*16), INVISIBLE,LIFE);

        //turtle
        new Turtle(QPoint(26*16, terrain_level));
        new Turtle(QPoint(42*16, terrain_level));

        // pipes

        new Pipe(QPoint(28*16, terrain_level), 0);
        new Pipe(QPoint(38*16, terrain_level), 1,DROP);
        new Pipe(QPoint(46*16, terrain_level), 2);

        // Mario
        mario = new Mario(QPoint(16*2.5, terrain_level));


        // Goombas
        new Goomba(QPoint(15*16, terrain_level), LEFT);
        new Goomba(QPoint(40*16, terrain_level));




    }
   else  if(level_name == "World-3")
    {
        // set background color
        scene->setBackgroundBrush(QBrush(QColor(190,231,233)));

        // terrain level
        int terrain_level = 200;

        // welcome message
        new Background(QPoint(40,terrain_level-5.5*16), ":/graphics/welcome.png");

        // terrain   制造地形中间的空格空白处
        new Terrain(QRect(0,terrain_level,69*16,30));
        new Terrain(QRect(71*16,terrain_level,15*16,30));

        // Mario
        mario = new Mario(QPoint(16*2.5, terrain_level));

    }
    else
        std::cerr << "Level not implemented";

    return mario;
}
