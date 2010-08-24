#ifndef GW_ENEMY_H
#define GW_ENEMY_H

#include "includes.h"
#include "entity.h"

class Bullet;

class Enemy : public Entity {
public:
	typedef Entity super;

	Enemy();

	int health;
	int ammoCount;

	int score;

	bool dead;
	sf::Clock deadClock;
	float corpseLife;
	void die();

	void checkBulletCollisions(const std::vector<Bullet*> &bullets);
	void getHit();

	virtual void update();
	virtual void render();
};

#endif
