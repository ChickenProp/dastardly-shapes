#ifndef GW_BULLET_H
#define GW_BULLET_H

#include "includes.h"
#include "entity.h"

class Bullet : public Entity {
public:
	Bullet(ph::vec2f pos, ph::vec2f vel);
	
	void update();
};

#endif
