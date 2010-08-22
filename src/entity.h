#ifndef GW_ENTITY_H
#define GW_ENTITY_H

#include "includes.h"

class Entity {
public:
	Entity();

	sf::Sprite sprite;
	float radius;

	ph::vec2f pos;
	ph::vec2f vel;
	float angle;

	bool trash;
	void markTrash();
	static bool deadPtr(Entity *ptr);

	virtual void update();
	virtual void render();

	bool colliding(Entity *other);
};

#endif
