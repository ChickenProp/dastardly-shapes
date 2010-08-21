#include "globals.h"

sf::RenderWindow G::window;
const sf::Input &G::input = G::window.GetInput();

sf::Clock G::clock;

int G::framerate = 60;

Screen *G::curScreen = NULL;
Game *G::gameScreen = NULL;

sf::Image G::Images::bullet;

bool G::loadImages () {
	bool succ = true;

	succ = succ && G::Images::bullet.LoadFromFile("media/bullet.tga");

	return succ;
}
