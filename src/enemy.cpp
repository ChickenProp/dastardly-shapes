#include "enemy.h"
#include "bullet.h"
#include "globals.h"
#include "game.h"
#include "sound.h"

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

	G::enemyMgr()->enemyDied(this);
	Sound::play(Sound::enemyKill);
}
	
float Enemy::deadTime() {
	return G::clock.GetElapsedTime() - diedAt;
}

void Enemy::update() {
	super::update();

	if (dead && deadTime() > corpseLife) {
		printf("enemy dies\n");
		markTrash();
	}
}

void Enemy::render() {
	// Make it really die before hitting 0 visibility, or we won't be able
	// to see it for some of its dead-time.
	if (dead)
		sprite.SetColor(sf::Color(128, 128, 128,
		                          255 - (200*deadTime()/corpseLife)));

	super::render();
}
