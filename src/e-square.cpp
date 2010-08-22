#include "e-square.h"
#include "globals.h"
#include "player.h"

E_Square::E_Square (ph::vec2f _pos) {
	pos = _pos;
	ammoCount = 10;
	corpseLife = 5;
	radius = 8;
	health = 3;

	sprite.SetImage(G::Images::enemy_square);
	sprite.SetCenter(64, 64);
	sprite.Resize(20, 20);
}

void E_Square::update () {
	super::update();

	if (!G::player())
		return;

	if (!dead)
		vel = accel_drag(G::player()->pos - pos, 150, 0.7);

	angle += 3;
	pos += vel;
}
