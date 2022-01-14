#include <QApplication>
#include "Game.h"

int main(int argc, char *argv[])
{
    // create Qt application
    QApplication app(argc, argv);

	// create and show the game
	Game::instance()->show();

    // launch Qt event loop
    return app.exec();
}
