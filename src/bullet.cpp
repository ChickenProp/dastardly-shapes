#include "bullet.h"
#include "globals.h"

Bullet::Bullet (ph::vec2f pos, ph::vec2f vel)
	: pos(pos),
	  vel(vel),
	  sprite(G::Images::bullet)
{
	sprite.SetCenter(16, 16); // the image is 32x32
	sprite.Resize(10,10);
}

void Bullet::update () {
	pos += vel;
}

void Bullet::render () {
	sprite.SetPosition(pos);
	G::window.Draw(sprite);
}
