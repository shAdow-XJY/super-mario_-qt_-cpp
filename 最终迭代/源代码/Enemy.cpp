#include "Enemy.h"

Enemy::Enemy() : Entity()
{
	// enemies are usually slow
	slow = true;

	// most enemies are usually hurtable
	hurtable = true;
}