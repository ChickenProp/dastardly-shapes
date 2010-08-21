#ifndef GW_GLOBALS_H
#define GW_GLOBALS_H

#include "includes.h"

class Screen;
class Game;

class G {
public:
	static sf::RenderWindow window;
	static const sf::Input &input;
	
	static int framerate;

	static Screen *curScreen;
	static Game *gameScreen;
};

#endif
