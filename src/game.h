#ifndef GW_GAME_H
#define GW_GAME_H

#include "screen.h"
#include "player.h"

class Game : public Screen {
public:
	Game();
	void update();
	void render();

	Player *player;
};

#endif