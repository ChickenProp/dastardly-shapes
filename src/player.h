#ifndef GW_PLAYER_H
#define GW_PLAYER_H

#include "includes.h"

class Player {
public:
	Player();

	sf::Image img;
	sf::Sprite sprite;

	ph::vec2f pos;
	ph::vec2f vel;
	ph::vec2f acc;
	float maxSpeed;
	float timeToHalf;

	float angle;

	int ammo;

	void update();
	void render();
};

#endif
