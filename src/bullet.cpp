#include "bullet.h"
#include "globals.h"

Bullet::Bullet (ph::vec2f _pos, ph::vec2f _vel) {
	pos = _pos;
	vel = _vel;

	sprite.SetImage(G::Images::bullet);
	sprite.SetCenter(16, 16); // the image is 32x32
	sprite.Resize(10,10);
}

void Bullet::update () {
	pos += vel;
}
