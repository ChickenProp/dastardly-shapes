#ifndef GW_ENTITY_H
#define GW_ENTITY_H

#include "includes.h"

class Entity {
public:
	sf::Sprite sprite;
	float radius;

	ph::vec2f pos;
	ph::vec2f vel;
	float angle;

	virtual void update();
	virtual void render();

	bool colliding(Entity *other);
};

#endif
