#include "e-triangle.h"
#include "globals.h"
#include "player.h"

E_Triangle::E_Triangle(ph::vec2f _pos) {
	pos = _pos;
	target = pos;
	ammoCount = 10;
	radius = 8;
	corpseLife = 10;
	rotationSpeed = 360; // degrees per second

	sprite.SetImage(G::Images::enemy_triangle);
	sprite.SetCenter(64, 64);
	sprite.Resize(20, 20);
}

void E_Triangle::update() {
	super::update();

	if (!G::player())
		return;

	if (!dead) {
		if (pos.distance(G::player()->pos) < 100)
			target = G::player()->pos;
		else if (pos.distance(target) < 30)
			selectNewTarget();

		approachTarget();
	}
	else
		pos += vel;
}

void E_Triangle::selectNewTarget () {
	ph::vec2f oldTarget = target;
	float playerAngle = (G::player()->pos - pos).angle();
	float targetAngle = ph::randf(90) - 45 + playerAngle;
	float targetDist = ph::randf(10) + 100;
	ph::vec2f offset = ph::vec2f::polar(targetDist, targetAngle);
	target = pos + offset;
}

void E_Triangle::approachTarget () {
	float angleStep = rotationSpeed / G::framerate;

	float targetAngle = (target - pos).angle();

	if (angle > targetAngle)
		angle = ph::max(targetAngle, angle - angleStep);
	if (angle < targetAngle)
		angle = ph::min(targetAngle, angle + angleStep);

	if (fabsf(angle - targetAngle) < 45)
		vel = accel_drag(ph::vec2f::polar(1, angle), 150, 0.3);

	pos += vel;
}
