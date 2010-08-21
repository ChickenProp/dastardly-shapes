#include "player.h"
#include "globals.h"

Player::Player ()
	: pos(320,240),
	  vel(0,0),
	  acc(0,0),
	  maxSpeed(640), // pixels per second
	  timeToHalf(0.5), // seconds to accelerate to maxSpeed/2
	  img(),
	  sprite()
{
	img.LoadFromFile("media/player.tga");
	sprite.SetImage(img);
}

void Player::update() {
	acc = ph::vec2f(0,0);

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
}

void Player::render() {
	sprite.SetPosition(pos);
	G::window.Draw(sprite);
}
