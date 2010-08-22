#ifndef GW_ENEMY_H
#define GW_ENEMY_H

#include "includes.h"
#include "entity.h"

class Bullet;

class Enemy : public Entity {
public:
	Enemy();

	int health;
	int ammoValue;

	bool dead;
	float diedAt;

	void checkBulletCollisions();
};

#endif
