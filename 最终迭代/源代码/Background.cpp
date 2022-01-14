#include "Background.h"
#include <QBitmap>

Background::Background(QPoint position, std::string _texture_path)
{
	// all background objects are not collidable
	collidable = false;

	// load texture
	texture_path = _texture_path;
	setPixmap(loadTexture(texture_path));

	// correct y-coordinate w.r.t. texture height
	setPos(position-QPoint(0, pixmap().height()));
}
