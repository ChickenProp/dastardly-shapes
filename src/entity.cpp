#include "entity.h"
#include "globals.h"

Entity::Entity ()
	: trash(false)
{}

void Entity::markTrash () {
	trash = true;
}

bool Entity::deadPtr (Entity *ptr) {
	return !ptr || ptr->trash;
}

void Entity::update () {
	// obviously this won't return from the caller, so we need to check for
	// trash there as well.
	if (trash) return;
}

void Entity::render () {
	if (trash) return;

	sprite.SetPosition(pos);
	sprite.SetRotation(-angle); // SFML angles are opposite to expected.
	G::window.Draw(sprite);
}

// Calculate the new velocity when accelerating in direction dir, given that
// drag prevents you from going faster than maxSpeed and causes you to take
// timeToHalf seconds to reach maxSpeed/2.
ph::vec2f Entity::accel_drag (ph::vec2f dir, float maxSpeed, float timeToHalf) {
	/* The applied force causes us to accelerate at a rate of A. Friction
	   causes us to deccelerate at a rate of B*v, where v is our current
	   velocity. If v = M, where M is our max speed, we require there to be
	   no acceleration. So B = A/M, and velocity is given by the
	   differential equation
	       dv/dt = A - v * A/M
	   where v=0 when t=0, and v=M/2 when t=T.

	   Solving this gives us A = M/T * ln(2).	   
	*/

	float M = maxSpeed / G::framerate;
	float T = timeToHalf * G::framerate;
	float A = M_LN2 * M / T;

	ph::vec2f acc = dir.normalize() * A - vel * A / M;

	return vel + acc;
}

bool Entity::colliding (Entity *other) {
	if (trash || deadPtr(other))
		return false;
	else
		return pos.distance(other->pos) < radius + other->radius;
}
