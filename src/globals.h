#ifndef GW_GLOBALS_H
#define GW_GLOBALS_H

#include "includes.h"

struct Screen;
struct Game;
struct Player;

class G {
public:
	static sf::RenderWindow window;
	static const sf::Input &input;

	static sf::Clock clock;

	static int framerate;

	static Screen *curScreen;
	static Game *gameScreen;

	static Player *player();

	struct Images {
		static sf::Image bullet;
		static sf::Image enemy_circle;
	};

	static bool loadImages();
};

#endif
