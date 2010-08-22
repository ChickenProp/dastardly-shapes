#include "enemy.h"
#include "bullet.h"
#include "globals.h"
#include "game.h"

Enemy::Enemy ()
	: dead(0)
{}

void Enemy::checkBulletCollisions() {
	// std::vectors copy each element, so if we didn't use a pointer and
	// tried to NULL some of the entries, the original wouldn't change.
	std::vector<Bullet*> *bullets = &G::gameScreen->bullets;

	for (int i = 0; i < bullets->size(); i++) {
		if (! (*bullets)[i] || ! colliding((*bullets)[i]))
			continue;

		dead = true;
		delete (*bullets)[i];
		(*bullets)[i] = NULL;
	}
}
