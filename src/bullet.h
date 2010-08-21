#ifndef GW_BULLET_H
#define GW_BULLET_H

#include "includes.h"

class Bullet {
public:
	Bullet(ph::vec2f pos, ph::vec2f vel);
	
	ph::vec2f pos;
	ph::vec2f vel;

	sf::Sprite sprite;

	void update();
	void render();
};

#endif
