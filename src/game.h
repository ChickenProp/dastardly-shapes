#ifndef GW_GAME_H
#define GW_GAME_H

#include "screen.h"

class Game : public Screen {
public:
	Game();
	void update();
	void render();
};

#endif
