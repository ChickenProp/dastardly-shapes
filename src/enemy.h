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

	bool dead;
	float diedAt;
	float corpseLife;
	float deadTime();

	void checkBulletCollisions(const std::vector<Bullet*> &bullets);
	void die();

	virtual void update();
	virtual void render();
};

#endif
