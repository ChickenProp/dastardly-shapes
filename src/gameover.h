#ifndef GW_GAMEOVER_H
#define GW_GAMEOVER_H

#include "screen.h"
#include "includes.h"

class GameOver : public Screen {
public:
	GameOver(int score, float time);

	sf::String string;

	void render();
	void update();
	void handleEvent(sf::Event e);
	void newGame();
};

#endif
