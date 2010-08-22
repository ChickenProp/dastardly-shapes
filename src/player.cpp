#include "player.h"
#include "game.h"
#include "globals.h"

Player::Player ()
	: maxSpeed(640), // pixels per second
	  timeToHalf(0.5), // seconds to accelerate to maxSpeed/2
	  ammo(100),
	  rateOfFire(5), // shots per second
	  timeLastShot(G::clock.GetElapsedTime())
{
	pos = ph::vec2f(320, 240);
	radius = 16;

	sprite.SetImage(G::Images::player);
	sprite.SetCenter(64, 64);

	// The image has a diameter of 128, and the circular bit has a diameter
	// of 96. We use this to size the sprite according to how large we want
	// the circular bit to appear.
	float scale = 128.0 / 96.0;
	sprite.Resize(2 * radius * scale, 2 * radius * scale);
}

void Player::update() {
	ph::vec2f acc(0,0);

	if (G::input.IsKeyDown(sf::Key::Left))
	        acc += ph::vec2f(-1, 0);
	if (G::input.IsKeyDown(sf::Key::Right))
	        acc += ph::vec2f(1, 0);
	if (G::input.IsKeyDown(sf::Key::Up))
	        acc += ph::vec2f(0, -1);
	if (G::input.IsKeyDown(sf::Key::Down))
	        acc += ph::vec2f(0, 1);

	acc = acc.normalize();

	/* The player causes us to accelerate at a rate of A. Friction causes us
	   to deccelerate at a rate of B*v, where v is our current velocity. If
	   v = M, where M is our max speed, we require no acceleration. So B =
	   A/M, and velocity is given by the differential equation
	       dv/dt = A - v * A/M
	   where v=0 when t=0, and v=M/2 when t=T.

	   Solving this gives us A = M/T * ln(2).	   
	*/

	float M = maxSpeed / G::framerate;
	float T = timeToHalf * G::framerate;
	float A = M_LN2 * M / T;

	acc = acc * A - vel * A / M;

	vel += acc;
	pos += vel;

	ph::vec2f mouse( G::input.GetMouseX(), G::input.GetMouseY() );
	angle = (mouse - pos).angle();

	if (G::input.IsMouseButtonDown(sf::Mouse::Left))
		tryToShoot();
}

bool Player::tryToShoot() {
	Bullet *bullet = new Bullet(pos + ph::vec2f::polar(radius, angle),
	                            vel + ph::vec2f::polar(10, angle));
	G::gameScreen->addBullet(bullet);
}

void Player::hitEnemy(Enemy *enemy) {
	if (! enemy->dead)
		exit(1);
	else {
		ammo += enemy->ammoCount;
		enemy->markTrash();
	}
}
