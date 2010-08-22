#ifndef GW_PLAYER_H
#define GW_PLAYER_H

#include "includes.h"
#include "entity.h"

class Player : public Entity {
public:
	Player();

	ph::vec2f acc;
	float maxSpeed;
	float timeToHalf;

	int ammo;
	int rateOfFire;
	int timeLastShot;
	bool tryToShoot();

	void update();
};

#endif
