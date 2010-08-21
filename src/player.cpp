#include "player.h"
#include "globals.h"

Player::Player ()
	: img(), sprite()
{
	img.LoadFromFile("media/player.tga");
	sprite.SetImage(img);
	sprite.SetPosition(320, 240);
}

void Player::render() {
	G::window.Draw(sprite);
}
