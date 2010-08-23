#include "enemy.h"
#include "player.h"
#include "bullet.h"
#include "enemy-manager.h"
#include "globals.h"
#include "game.h"
#include "sound.h"

Enemy::Enemy ()
	: dead(0),
	  health(1) // default
{}

void Enemy::checkBulletCollisions(const std::vector<Bullet*> &bullets) {
	if (dead)
		return;

	for (int i = 0; i < bullets.size(); i++) {
		if (! bullets[i] || ! colliding(bullets[i]))
			continue;

		float angle = bullets[i]->vel.angle();
	        G::gameScreen->addParticles(pos, bullets[i]->vel / 10,//ph::vec2f::polar(1, angle),
		                            50);
		getHit();
		bullets[i]->markTrash();
	}
}

void Enemy::getHit () {
	health--;
	if (health <= 0)
		die();
	else
	Sound::play(Sound::enemyHit);
}

void Enemy::die() {
	dead = true;
	diedAt = G::clock.GetElapsedTime();

	if (G::player())
		G::player()->score += score;

	G::enemyMgr()->enemyDied(this);
	Sound::play(Sound::enemyKill);
}
	
float Enemy::deadTime() {
	return G::clock.GetElapsedTime() - diedAt;
}

void Enemy::update() {
	super::update();

	if (dead && deadTime() > corpseLife) {
		markTrash();
	}

	if (! G::player())
		pos += vel;

	G::gameScreen->addParticles(pos, -vel, 1, 100, 5000);
}

void Enemy::render() {
	// Make it really die before hitting 0 visibility, or we won't be able
	// to see it for some of its dead-time.
	if (dead)
		sprite.SetColor(sf::Color(128, 128, 128,
		                          255 - (200*deadTime()/corpseLife)));

	super::render();
}
