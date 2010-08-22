#include "entity.h"
#include "globals.h"

Entity::Entity ()
	: trash(false)
{}

void Entity::markTrash () {
	trash = true;
}

void Entity::update () {
	if (trash) return;
}

void Entity::render () {
	if (trash) return;

	sprite.SetPosition(pos);
	sprite.SetRotation(-angle); // SFML angles are opposite to expected.
	G::window.Draw(sprite);
}

bool Entity::colliding (Entity *other) {
	return pos.distance(other->pos) < radius + other->radius;
}
