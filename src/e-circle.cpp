#include "e-circle.h"
#include "globals.h"
#include "player.h"

E_Circle::E_Circle (ph::vec2f _pos) {
	pos = _pos;
	radius = 8;
	corpseLife = 10;
	ammoCount = 10;
	sprite.SetImage(G::Images::enemy_circle);
	sprite.SetCenter(64, 64); // the image is 128x128
	sprite.Resize(radius*2, radius*2);
}

void E_Circle::update () {
	Enemy::update();

	Player *player = G::player();
	if (!player)
		return;

	if (!dead) {
		ph::vec2f in = (player->pos - pos).normalize();
		ph::vec2f orb = ph::vec2f(in.y, -in.x);
		vel = (in + 3*orb).normalize();
	}

	pos += vel;
}
