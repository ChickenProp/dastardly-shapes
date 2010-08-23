#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include "globals.h"
#include "sound.h"

Player::Player ()
	: score(0),
	  maxSpeed(640), // pixels per second
	  timeToHalf(0.2), // seconds to accelerate to maxSpeed/2
	  maxAmmo(20),
	  ammo(20),
	  rateOfFire(5), // shots per second
	  rateOfDryFire(1), // shots per second
	  shotClock()
{
	pos = ph::vec2f(285, 285);
	radius = 12;

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

	vel = accel_drag(acc, maxSpeed, timeToHalf);
	pos += vel;

	bool bounce = false;
	float bounceVel = 0;
	int width = G::window.GetWidth();
	int height = G::window.GetHeight();
	float rest = 0.8f;

	if (pos.x - radius <= 0) {
		vel = ph::vec2f(-vel.x*rest, vel.y);
		bounceVel = fabs(vel.x);
		pos.x = radius;
		bounce = true;
	}
	else if (pos.x + radius >= width) {
		vel = ph::vec2f(-vel.x*rest, vel.y);
		bounceVel = fabs(vel.x);
		pos.x = width - radius;
		bounce = true;
	}

	if (pos.y - radius <= 0) {
		vel = ph::vec2f(vel.x, -vel.y*rest);
		bounceVel = fabs(vel.y);
		pos.y = radius;
		bounce = true;
	}
	else if (pos.y + radius >= height) {
		vel = ph::vec2f(vel.x, -vel.y*rest);
		bounceVel = fabs(vel.y);
		pos.y = height - radius;
		bounce = true;
	}

	if (bounce && bounceVel >= 0.5) {
		Sound::play(Sound::bounce, false, 1.0f,
		            ph::min(bounceVel - 0.5f, 3.f) * 100.f / 3.f);
	}

	ph::vec2f mouse( G::input.GetMouseX(), G::input.GetMouseY() );
	angle = (mouse - pos).angle();

	if (G::input.IsMouseButtonDown(sf::Mouse::Left)
	    && canShoot())
		shoot();
}

bool Player::canShoot() {
	if (ammo > 0)
		return shotClock.GetElapsedTime() > 1.0/rateOfFire;
	else
		return shotClock.GetElapsedTime() > 1.0/rateOfDryFire;
}

void Player::shoot() {
	Bullet *bullet = new Bullet(pos + ph::vec2f::polar(radius, angle),
	                            vel + ph::vec2f::polar(10, angle));
	G::gameScreen->addBullet(bullet);

	ammo = ph::max(ammo-1, 0);
	shotClock.Reset();

	printf("ammo: %d\n", ammo);

	Sound::play(Sound::shoot, false, 2.0 - (float)ammo/maxAmmo);
}

void Player::hitEnemy(Enemy *enemy) {
	if (! enemy->dead) {
		angle = (pos - enemy->pos).angle();
		
		G::gameScreen->addParticles(pos, ph::vec2f::polar(2, angle),
		                            500, 120);
		G::gameScreen->gameOver();
	}
	else {
		ammo += enemy->ammoCount;
		ammo = ph::min(ammo, maxAmmo);
		score += enemy->score;
		enemy->markTrash();
		Sound::play(Sound::pickupEnemy);
	}
}
