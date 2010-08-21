#include "globals.h"
#include "game.h"

sf::RenderWindow G::window;
const sf::Input &G::input = G::window.GetInput();

sf::Clock G::clock;

int G::framerate = 60;

Screen *G::curScreen = NULL;
Game *G::gameScreen = NULL;

sf::Image G::Images::bullet;
sf::Image G::Images::enemy_circle;

Player *G::player () {
	if (!gameScreen)
		return NULL;
	return gameScreen->player;
}

bool G::loadImages () {
	bool succ = true;

	succ = succ && G::Images::bullet.LoadFromFile("media/bullet.tga");
	succ = succ && G::Images::enemy_circle.LoadFromFile("media/enemy-circle.tga");

	return succ;
}
