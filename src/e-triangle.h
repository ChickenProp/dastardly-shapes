#ifndef GW_E_TRIANGLE
#define GW_E_TRIANGLE

#include "includes.h"
#include "enemy.h"

class E_Triangle : public Enemy {
public:
	typedef Enemy super;

	E_Triangle(ph::vec2f pos);

	void update();

	float rotationSpeed;

	ph::vec2f target;
	void selectNewTarget();
	void approachTarget();
};

#endif
