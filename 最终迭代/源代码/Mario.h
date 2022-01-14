#pragma once

#include "Entity.h"

class Mario : public Entity
{
	protected:

		// physics parameters
		static const int jump_duration_tiny  = 30;	// when Mario jumps over enemies
		static const int jump_duration_small = 70;	// when small Mario jumps
		static const int jump_duration_big   = 90;	// when big Mario jumps


		// animation divisors (inversely proportional to animation speed)
		static const int walk_div    = 6;			// walking animation
		static const int running_div = 4;			// running animation
		static const int transf_div  = 5;			// transformation animation

		// textures
		QPixmap texture_walk[2][3];			// small/big walking animation (3 textures)
		QPixmap texture_stand[2];			// small/big stand texture
		QPixmap texture_jump[2];			// small/big jump texture
		QPixmap texture_dead;				// Mario dies
		QPixmap texture_small_to_big[4];	// Mario small to big transformation

		// flags
		bool big;							// is Mario big?
		bool fire;							// can Mario fire?
		bool bouncing;						// is Mario bouncing on enemies?
		bool running;						// is Mario running?
		bool transforming;					// is Mario transforming? (e.g. from big to small)
        ////////////////////////////////
        //piping
        int walk_duration;
        bool piping;
        bool piping1;
        bool piping2;
        bool piped;
        /// /////////////////////////////

        ///////////////
        int life=1;
        //////////////

		// counters
		int transformation_counter;

		// durations (= limits for counters)
		int transformation_duration;

		// UTILITY METHODS

		// bounce on enemies
		void bounce();

		// start/end transformation
		void startTransformation();
		void endTransformation();

        ///////////////////////////////////
        /// \brief success
        bool successing;
        bool success;
        int castle_x;
        int castle_y;
        //////////////////////////////////
	public:

		Mario(QPoint position);

        //////////////////////////
        bool isSuccessing(){return successing;};
        bool isSuccess(){return success;};
        /////////////////////////


		// getters and setters
		bool isBig(){return big;}
		bool isTransforming(){return transforming;}
		void setRunning(bool _running);

        // pure virtual methods that must be implemented
        virtual std::string name(){ return "Mario";}
        virtual void animate();
        virtual void hit(Object *what, Direction fromDir);

		// override die method so we can play Mario death animation
		virtual void die();

		// Mario eats a (red = default) Mushroom and gets big
		void mushroomEat(bool red = true);

		// Mario eats a Flower and can fire
		void flowerEat();
        /////////////////////////////////////////
        void Firefight();
        ////////////////////////////////////////

        ///////////////////////////////////////////
        //Mario jump into a pipe
        void pipejump();
        void setpipe(bool a){piping = a;};
        void setpipe1(bool b){piping1 = b;};
        bool ispiped(){return piped;};
        //////////////////////////////////////////////

		// Mario is hurt
		void hurt();

        // jump
        void jump();

        /////////////////////////////
        void castleAddress(int x,int y);
};
