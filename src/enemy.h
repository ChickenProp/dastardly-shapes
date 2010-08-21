#ifndef GW_ENEMY_H
#define GW_ENEMY_H

#include "includes.h"

class Enemy {
public:
	sf::Sprite sprite;

	ph::vec2f pos;
	ph::vec2f vel;
	ph::vec2f acc;

	int health;
	int ammoValue;

	bool dead;
	float diedAt;

	virtual void update()=0;
	virtual void render()=0;
};

#endif
