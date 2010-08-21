#include "player.h"
#include "globals.h"

Player::Player ()
	: pos(320,240),
	  vel(0,0),
	  acc(0,0),
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

	acc = acc.normalize()*0.05;

	vel += acc;
	pos += vel;	
}

void Player::render() {
	sprite.SetPosition(pos);
	G::window.Draw(sprite);
}
