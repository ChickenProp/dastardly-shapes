#ifndef GW_GAME_H
#define GW_GAME_H

#include "screen.h"
#include "includes.h"

class Player;
class Bullet;
class EnemyMgr;
class GameOver;

class Game : public Screen {
public:
	Game();
	void update();
	void render();

	void handleEvents();
	void handleEvent(sf::Event e);

	sf::Sprite backdrop;

	Player *player;

	void addBullet(Bullet* bullet);
	std::vector<Bullet*> bullets;

	EnemyMgr *enemies;

	void handleCollisions();

	bool isGameOver;
	sf::Clock gameOverClock;
	void gameOver();
	GameOver *gameOverScreen;
};

#endif
