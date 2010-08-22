#ifndef GW_ENEMY_H
#define GW_ENEMY_H

#include "includes.h"
#include "entity.h"

class Enemy : public Entity {
public:
	int health;
	int ammoValue;

	bool dead;
	float diedAt;
};

#endif
