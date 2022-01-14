#include "Block.h"
#include <QSound>

Block::Block(QPoint position) : Inert()
{
	setPixmap(QPixmap(loadTexture(":/graphics/block.png")));
	setPos(position);
}

void Block::hit(Object *what, Direction fromDir)
{
    if(fromDir == DOWN)
        QSound::play(":/sounds/block-hit.wav");
}
