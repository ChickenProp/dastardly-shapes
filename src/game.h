#ifndef GW_GAME_H
#define GW_GAME_H

#include "globals.h"
#include "screen.h"
#include "player.h"
#include "bullet.h"
#include "enemy-manager.h"

class Game : public Screen {
public:
	Game();
	void update();
	void render();

	void handleEvents();
	void handleEvent(sf::Event e);

	Player *player;

	void addBullet(Bullet* bullet);
	std::vector<Bullet*> bullets;

	EnemyMgr *enemies;

	void handleCollisions();
};

#endif
