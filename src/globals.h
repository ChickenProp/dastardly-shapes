#ifndef GW_GLOBALS_H
#define GW_GLOBALS_H

#include "includes.h"

class Screen;
class Game;
class Player;
class EnemyMgr;

class G {
public:
	static sf::RenderWindow window;
	static const sf::Input &input;

	static sf::Clock clock;

	static int framerate;

	static Screen *curScreen;
	static Game *gameScreen;

	static Player *player();
	static EnemyMgr *enemyMgr();

	struct Images {
		static sf::Image backdrop;
		static sf::Image player;
		static sf::Image bullet;
		static sf::Image enemy_circle;
	};

	static bool loadImages();
};

#endif
