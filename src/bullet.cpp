#include "bullet.h"
#include "globals.h"
#include "game.h"

Bullet::Bullet (ph::vec2f _pos, ph::vec2f _vel) {
	pos = _pos;
	vel = _vel;

	sprite.SetImage(G::Images::bullet);
	sprite.SetCenter(16, 16); // the image is 32x32
	sprite.Resize(10,10);
}

void Bullet::update () {
	super::update();

	pos += vel;

	G::gameScreen->addParticles(pos, -vel/10, 1, 20, 5000);
}
