#include "globals.h"

sf::RenderWindow G::window;
const sf::Input &G::input = G::window.GetInput();

sf::Clock G::clock;

int G::framerate = 60;

Screen *G::curScreen = NULL;
Game *G::gameScreen = NULL;
