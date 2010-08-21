#include "bullet.h"
#include "globals.h"

Bullet::Bullet (ph::vec2f pos, ph::vec2f vel)
	: pos(pos),
	  vel(vel),
	  sprite(G::Images::bullet)
{
	sprite.Resize(10,10);
	sprite.SetCenter(5,5);
}

void Bullet::update () {
	pos += vel;
}

void Bullet::render () {
	sprite.SetPosition(pos);
	G::window.Draw(sprite);
}
