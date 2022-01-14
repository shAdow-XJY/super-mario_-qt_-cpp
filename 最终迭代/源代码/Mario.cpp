#include "Mario.h"
#include "Enemy.h"
#include "Game.h"
#include <QSound>

#include"fireball.h"
#include"Castle.h"
Mario::Mario(QPoint position) : Entity()
{
	// set flags
	moving  = false;
	running = false;
	bouncing = false;
	big = false;
	fire = false;
	transforming = false;
	transformation_counter = 0;

	// durations
	jumping_duration = jump_duration_small;
	death_duration = 300;
    walk_duration = 200;
	transformation_duration = freeze_duration;

	// textures
	texture_walk[0][0] = QPixmap(loadTexture(":/graphics/mario-small-walk-0.png"));
	texture_walk[0][1] = QPixmap(loadTexture(":/graphics/mario-small-walk-1.png"));
	texture_walk[0][2] = QPixmap(loadTexture(":/graphics/mario-small-walk-2.png"));
	texture_walk[1][0] = QPixmap(loadTexture(":/graphics/mario-big-walk-0.png"));
	texture_walk[1][1] = QPixmap(loadTexture(":/graphics/mario-big-walk-1.png"));
	texture_walk[1][2] = QPixmap(loadTexture(":/graphics/mario-big-walk-2.png"));
	texture_stand[0]   = QPixmap(loadTexture(":/graphics/mario-small-stand.png"));
	texture_stand[1]   = QPixmap(loadTexture(":/graphics/mario-big-stand.png"));
	texture_jump[0]    = QPixmap(loadTexture(":/graphics/mario-small-jump.png"));
	texture_jump[1]    = QPixmap(loadTexture(":/graphics/mario-big-jump.png"));
	texture_dead	   = QPixmap(loadTexture(":/graphics/mario-small-fall.png"));
	texture_small_to_big[0] = texture_stand[0];
	texture_small_to_big[1] = QPixmap(loadTexture(":/graphics/mario-med-stand.bmp"));
	texture_small_to_big[2] = texture_stand[1];
	texture_small_to_big[3] = QPixmap(loadTexture(":/graphics/mario-med-stand.bmp"));

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_stand[0]);
	setPos(position-QPoint(0, pixmap().height()));

	// Mario is at a higher layer than other objects
	setZValue(3);

    //////////////////////////
    //castle
    successing=false;
    success=false;
    castle_x=0;
    castle_y=0;

    //pipe
    piping = false;
    piping1 = false;
    piping2 = false;
    piped = false;
    /////////////////////////
}
////////////////////////////
void Mario::castleAddress(int x,int y)
{
    successing=true;
    castle_x=x;
    castle_y=y;
}
/////////////////////////////
// Mario jumps
void Mario::jump()
{
	// do nothing if already jumping
	if(jumping)
		return;

    // start a jump
    startJumping();

    // if jumping has started, play jump sound
    if(jumping)
        QSound::play(big ? ":/sounds/jump-big.wav" : ":/sounds/jump-small.wav");
}

///////////////////////////////////////////////////////
void Mario::pipejump()
{
    moving_speed = walk_counter%8 ==0;
    setY(y() + moving_speed);
}
///////////////////////////////////////////////////////

// Mario eats a (red = default) Mushroom and gets big
void Mario::mushroomEat(bool red)
{
	if(red)
	{
		// get big if not already
		if(!big)
		{
			big = true;

			// set proper jump duration
			jumping_duration = jump_duration_big;

			// start transformation
			startTransformation();
		}

		// play sound in any case
		QSound::play(":/sounds/mushroom-eat.wav");
	}
    // green: life up
	else
    {
        life+=1;
		QSound::play(":/sounds/oneup.wav");
    }
}

// Mario eats a Flower and can fire
void Mario::flowerEat()
{
    ///////////////////////////////////
    fire=true;
    //////////////////////////////////
	// to be implemented
	QSound::play(":/sounds/mushroom-eat.wav");
}
/////////////////////////////////////
void Mario::Firefight()
{
    if(fire)
    {
      //  pixmap().width()
        int dx = (big ? texture_stand[1] : texture_stand[0]).width();
        int dy = (big ? texture_stand[1] : texture_stand[0]).height()/2;

        if(dir==LEFT)
        {
        new Fireball(QPoint(x()-dx,y()+dy),dir);
        }
        else {
            new Fireball(QPoint(x()+dx,y()+dy),dir);
        }
    }
}
/////////////////////////////////////
// Mario is hurt
void Mario::hurt()
{
	// cannot fire anymore
	fire = false;

	// if big, gets small
	if(big)
	{
		big = false;

		// set proper jump duration
		jumping_duration = jump_duration_small;

		// play sound
		QSound::play(":/sounds/shrink.wav");

		// Mario becomes a phantom temporarily
		startPhantom();

		// start transformation
		startTransformation();
	}
    else if(life>1)
    {
        life-=1;
        // play sound
        QSound::play(":/sounds/shrink.wav");

        // Mario becomes a phantom temporarily
        startPhantom();

        // start transformation
         startTransformation();
    }
	// otherwise, Mario dies
	else
		die();
}

// start transformation
void Mario::startTransformation()
{
	// start transformation
	transforming = true;

	// set animation counter so that next animation
	// is properly handled (see animate())
	transformation_counter = big ? 0 : 2*transf_div;

	// freeze
	freeze();
}

// end transformation
void Mario::endTransformation()
{
	// end transformation
	transforming = false;

	// reset animation counter
	transformation_counter = 0;

	// correct y coordinate so that the 'final' (transformed) Mario
	// has the same bottom coordinate 
    ///////////////////////////////////////////////////////////////////////////////
	int dy = pixmap().height()-(big ? texture_stand[1] : texture_stand[0]).height();
    if(big)
    {
	setY(y()+dy);
    }
    else
    {
        setY(y()-texture_stand[0].height());
    }
    ////////////////////////////////////////////////////////////////////////////////
}


void Mario::animate()
{
	// handle bouncing
	if(jumping == false && bouncing)
	{
		bouncing = false;
		jumping_duration = big ? jump_duration_big : jump_duration_small;
	}

	// handle phantom mode
	if(phantom)
	{
		phantom_counter++;
		if(phantom_counter > phantom_duration)
			endPhantom();
	}

	// handle transformation
	if(transforming)
	{
		transformation_counter++;
		if(transformation_counter > transformation_duration)
			endTransformation();
	}

	// set proper texture
	if(transforming)
	{
		int prev = ((transformation_counter-1)/transf_div)%4;
		int curr = (transformation_counter/transf_div)%4;
		int dy = texture_small_to_big[prev].height()-texture_small_to_big[curr].height();
		setPixmap(texture_small_to_big[(transformation_counter/transf_div)%4]);
		setY(y()+dy);
	}
	else if(dying || dead)
		setPixmap(texture_dead);
	else if(moving && !jumping && !falling)
		setPixmap(texture_walk[big][(walk_counter++/(running ? running_div : walk_div))%3]);
	else if(jumping || falling)
		setPixmap(texture_jump[big]);
	else
		setPixmap(texture_stand[big]);

    ///////////////////////////////////////////////
    //Castle event
    if(successing)
    {
        if(y()>castle_y)
        {
            if(castle_x==x())
           {
               success=true;
           }
        }
    }

    //pipe
    if(falling)
    {
        setpipe1(false);
    }

    if(piping1 && piping)
    {
        piping2 = true;
    }


    if(piping2 == true)
    {
        walk_counter++;
        pipejump();
        int time_pipe_down=walk_duration;
        if(big)
            time_pipe_down*=2;
        if(walk_counter>2*time_pipe_down)
        {
            piped = true;
        }

    }
    /////////////////////////////////////////////////

	// mirror the texture along the horizontal axis if needed
    //¾µÏñ£¬×ø±ê¶Ô³Æ
	if(dir == LEFT)
		setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

// Mario has been hit
void Mario::hit(Object *what, Direction fromDir)
{
	// if hit by Enemy
	Enemy *enemy = dynamic_cast<Enemy*>(what);
	if(enemy)
	{
		// with Mario's feet and enemy is hurtable --> enemy is hurt
		if(fromDir == DOWN && enemy->isHurtable())
		{
			// hurt enemy and bounce
			enemy->hurt();
			bounce();
		}
		// all other cases   --> Mario is hurt
		else
        {
            hurt();
        }
        return;
	}
/*
    Castle *castle = dynamic_cast<Castle*>(what);
    if(castle)
    {
        startPhantom();
    }
*/
}

// bounce on enemies
void Mario::bounce()
{
	falling = false;
	bouncing = true;
	jumping_duration = jump_duration_tiny;
	startJumping();
}

// override die method so we can play Mario death animation
void Mario::die()
{
	// call superclass method
	Entity::die();

	// in addition, we make Mario not collidable
	// so he can fall through all objects (including Terrain)
	collidable = false;

	// play death sound while stopping level music
	QSound::play(":/sounds/death.wav");
	Game::instance()->stopMusic();

	// freeze Mario before jumping
	freeze();

	// make a slow jump
	jumping_speed = 1;
	falling_speed = 1;
	startJumping();
}


// running = double moving speed
void Mario::setRunning(bool _running)
{
	// do nothing if running state does not change
	if(running == _running)
		return;

	// set new running state
	running = _running;

	// double / halve moving speed
	if(running)
		moving_speed *= 2;
	else
		moving_speed /= 2;
}
