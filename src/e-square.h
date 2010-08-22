#ifndef GW_E_SQUARE_H
#define GW_E_SQUARE_H

#include "enemy.h"
#include "includes.h"

class E_Square : public Enemy {
public:
	typedef Enemy super;

	E_Square(ph::vec2f pos);

	void update();
};

#endif
