#ifndef GW_GAME_H
#define GW_GAME_H

#include "globals.h"
#include "screen.h"
#include "player.h"
#include "bullet.h"

class Game : public Screen {
public:
	Game();
	void update();
	void render();

	void handleEvents();
	void handleEvent(sf::Event e);

	Player *player;
	Bullet *bullet;
};

#endif
