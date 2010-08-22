#ifndef GW_PLAYER_H
#define GW_PLAYER_H

#include "includes.h"
#include "entity.h"

class Enemy;

class Player : public Entity {
public:
	typedef Entity super;

	Player();

	ph::vec2f acc;
	float maxSpeed;
	float timeToHalf;

	int ammo;
	int rateOfFire;
	float timeLastShot;
	bool tryToShoot();
	void shoot();

	void update();

	void hitEnemy(Enemy *enemy);
};

#endif
