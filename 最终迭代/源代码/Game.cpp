#include <QApplication>
#include <QKeyEvent>
#include <QScrollBar>
#include <QWheelEvent>
#include <QSound>
#include <QThread>
#include "Game.h"
#include "Object.h"
#include "Entity.h"
#include "Mario.h"

// Singleton design pattern
Game* Game::uniqueInstance = 0;
Game* Game::instance()
{
	if(uniqueInstance == 0)
		uniqueInstance = new Game();
	return uniqueInstance;
}


Game::Game(QGraphicsView *parent) : QGraphicsView(parent)
{
    // setup scene/view
	scene = new QGraphicsScene();
	setScene(scene);
	scale(2.0,2.0);
	centerOn(0,0);
	setInteractive(false);
	setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	scene->setSceneRect(0, 0, 10000, 225);

    // setup game engine
    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    engine.setInterval(10);

	// setup game music
	music = new QSound(":/sounds/overworld.wav");
	music->setLoops(QSound::Infinite);
	mario = 0;
	reset();

	// setup window size
	this->setFixedHeight(2.0 * 225);
	this->setFixedWidth(800);
}

// reset game
void Game::reset()
{
	cur_state = READY;
	mario = 0;
	engine.stop();
	music->stop();
	scene->clear();
	scene->setBackgroundBrush(QBrush(Qt::white));

	// display welcome message
	QGraphicsTextItem* text = scene->addText("Press \"S\" to start a new game");
	text->setPos(300,90);
	centerOn(text);
}

// game over
void Game::gameover()
{
	// stop game
	cur_state = GAME_OVER;
	engine.stop();

	// set black background
	scene->setBackgroundBrush(QBrush(Qt::black));

	// play game over sound
    if(!mario->isSuccess())
	QSound::play(":/sounds/gameover.wav");
}

// start new game
void Game::start()
{
	if(cur_state == READY)
	{
		scene->clear();
		engine.start();
        mario = LevelManager::load("World-"+QString::number(level_number), scene);

		if(!mario)
		{
			scene->setBackgroundBrush(QBrush(QColor(242,204,204)));
			QGraphicsTextItem* text = scene->addText("Error when loading level");
			text->setPos(300,90);
			centerOn(text);
		}
		else
			music->play();

		cur_state = RUNNING;
	}
}

// pause / resume game
void Game::tooglePause()
{
	if(cur_state == RUNNING)
	{
		engine.stop();
		music->stop();
		cur_state = PAUSE;
		QSound::play(":/sounds/pause.wav");
	}
	else if(cur_state == PAUSE)
	{
		engine.start();
		music->play();
		cur_state = RUNNING;
	}
}

// stop music
void Game::stopMusic()
{
	if(music)
		music->stop();
}

void Game::keyPressEvent(QKeyEvent *e)
{
	// start new game
	if(e->key() == Qt::Key_S && cur_state == READY)
		start();

	// reset game
	if(e->key() == Qt::Key_R || cur_state == GAME_OVER)
		reset();

	// pause game
	if(e->key() == Qt::Key_P)
		tooglePause();

	// from now on, all commands require the game to be running
	if(cur_state != RUNNING)
		return;

    // horizontal Mario's movements
    if(e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
    {
        mario->setMoving(true);
        mario->setDirection(e->key() == Qt::Key_Right ? Direction::RIGHT : Direction::LEFT);
    }

    // Mario's jump
    if(e->key() == Qt::Key_Space)
        mario->jump();

    if(e->key() == Qt::Key_Down)
        mario->setpipe(true);

	// Mario's running
	if(e->key() == Qt::Key_Z)
		mario->setRunning(true);

    /////////////////////////////////////////////////////////////////
    // experimental (to be removed) : Mario fire a ball
    if(e->key() == Qt::Key_B)
        mario->Firefight();
    /////////////////////////////////////////////////////////////////
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
	// from now on, all commands require the game to be running
	if(cur_state != RUNNING)
		return;

    // horizontal Mario's movements
    if(e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
        mario->setMoving(false);

	// Mario's running
	if(e->key() == Qt::Key_Z)
		mario->setRunning(false);

    ///////////////////////////////////
    if(e->key() == Qt::Key_Down)
        {
            mario->setpipe(false);
        }
    //////////////////////////////////
}

// zoom-in/out
void Game::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0)
        scale(1.1, 1.1);
    else
        scale(1/1.1, 1/1.1);
}

void Game::advance()
{
	// do nothing if game is not running
	if(cur_state != RUNNING)
		return;

	// if mario is dead, game over
	if(mario->isDead())
		gameover();

	// if mario is dying or transforming, animate/advance only him
	// (the rest of the world is freezed)
	if(mario->isDying() || mario->isTransforming())
	{	
		mario->animate();
		mario->advance();
		return;
	}

    if(mario->ispiped())
    {
        gameover();
        cur_state=READY;
        level_number++;
        start();
    }

    ///////////////////////////////////////////
    if(mario->isSuccess())
    {
        gameover();
        cur_state=READY;
        level_number++;
        start();
    }
    ///////////////////////////////////////////

	// tell all game objects to animate and advance in the scene
    for(auto & item : scene->items())
    {
		Object* obj = dynamic_cast<Object*>(item);
		if(obj)
		{
			obj->animate();
			obj->advance();

			// destroy died Entity objects
			Entity* entity_obj = dynamic_cast<Entity*>(obj);
			if(entity_obj && entity_obj->isDead())
			{
				//printf("%s (%.0f,%.0f) destroyed\n", entity_obj->name().c_str(), entity_obj->pos().x(), entity_obj->pos().y());
				scene->removeItem(entity_obj);
				delete entity_obj;
			}
		}
    }

    // center view on Mario
    centerOn(mario);
}
