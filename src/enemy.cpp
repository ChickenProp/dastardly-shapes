#include "enemy.h"
#include "bullet.h"
#include "globals.h"
#include "game.h"

Enemy::Enemy ()
	: dead(0)
{}

void Enemy::checkBulletCollisions(const std::vector<Bullet*> &bullets) {
	if (dead)
		return;

	for (int i = 0; i < bullets.size(); i++) {
		if (! bullets[i] || ! colliding(bullets[i]))
			continue;

		die();
		bullets[i]->markTrash();
	}
}

void Enemy::die() {
	dead = true;
	diedAt = G::clock.GetElapsedTime();
	sprite.SetColor(sf::Color(128, 128, 128));
}

void Enemy::update() {
	super::update();

	if (dead && G::clock.GetElapsedTime() - diedAt > 2)
		markTrash();
}
