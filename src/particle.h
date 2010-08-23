#ifndef GW_PARTICLE_H
#define GW_PARTICLE_H

#include "includes.h"

class Particle {
public:
	ph::vec2f pos;
	ph::vec2f vel;
	sf::Color color;

	char unused[12]; //pad to 32 bytes

	Particle (ph::vec2f pos, ph::vec2f vel)
		: pos(pos), vel(vel), color(255, 255, 255, 255) {}

	void update () { // assume 60fps for speed. Probably unnecessary.
		pos += vel;
		if (color.a)
			color.a--;
	}
};

#endif
