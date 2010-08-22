#include "entity.h"
#include "globals.h"

void Entity::update () {}

void Entity::render () {
	sprite.SetPosition(pos);
	sprite.SetRotation(-angle); // SFML angles are opposite to expected.
	G::window.Draw(sprite);
}

bool Entity::colliding (Entity *other) {
	return pos.distance(other->pos) < radius + other->radius;
}
