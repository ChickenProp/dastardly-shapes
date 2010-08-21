#include "globals.h"

sf::RenderWindow G::window;
const sf::Input &G::input = G::window.GetInput();

Screen *G::curScreen = NULL;
Game *G::gameScreen = NULL;
