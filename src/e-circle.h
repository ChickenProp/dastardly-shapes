#ifndef GW_E_CIRCLE_H
#define GW_E_CIRCLE_H

#include "enemy.h"

class E_Circle : public Enemy {
public:
	E_Circle(ph::vec2f pos);
	void update();
	void render();
};

#endif
