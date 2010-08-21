#include "e-circle.h"
#include "globals.h"
#include "player.h"

E_Circle::E_Circle (ph::vec2f _pos) {
	pos = _pos;
	sprite.SetImage(G::Images::enemy_circle);
	sprite.SetCenter(64, 64); // the image is 128x128
	sprite.Resize(16, 16);
}

void E_Circle::update () {
	Player *player = G::player();
	if (!player)
		return;

	ph::vec2f in = (player->pos - pos).normalize();
	ph::vec2f orb = ph::vec2f(in.y, -in.x);
	vel = (in + 3*orb).normalize();

	pos += vel;
}

void E_Circle::render () {
	sprite.SetPosition(pos);
	G::window.Draw(sprite);
}
