#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QSound>

#include "Mario.h"
#include "LevelManager.h"

class Game : public QGraphicsView 
{ 
	Q_OBJECT 
	
	enum game_state{READY, RUNNING, PAUSE, GAME_OVER};

	private:

		static Game* uniqueInstance;	// Singleton design pattern
		Game(QGraphicsView *parent=0);	// Singleton design pattern

        QGraphicsScene *scene;          // the scene used to render the game (2D)
        Mario *mario;                   // mario object
        QTimer engine;                  // game engine / timer
		game_state cur_state;           // current game state
		QSound *music;					// game music

        ///////////////////////////////////////////////////////
        int level_number=1;
        //////////////////////////////////////////////////////

	protected:

        // the game is controlled using the keyboard
        // hence we have to intercept all keyboard events
		virtual void keyPressEvent(QKeyEvent *e);
		virtual void keyReleaseEvent(QKeyEvent *e);

        // zoom-in/out
        virtual void wheelEvent(QWheelEvent *e);

	public: 
		
		// get unique instance
		static Game* instance();

		// getters
		QGraphicsScene* getScene(){return scene;}

	public slots:

        // advance game / next frame
        void advance();

		// pause / resume game
		void tooglePause();

		// reset game
		void reset();

		// start new game
		void start();

		// game over
		void gameover();

		// stop music
		void stopMusic();
};
