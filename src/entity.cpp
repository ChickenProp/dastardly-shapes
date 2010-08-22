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

bool Entity::colliding (Entity *other) {
	if (trash || deadPtr(other))
		return false;
	else
		return pos.distance(other->pos) < radius + other->radius;
}
