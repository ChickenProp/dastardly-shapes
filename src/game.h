#ifndef GW_GAME_H
#define GW_GAME_H

#include "screen.h"
#include "includes.h"

class Player;
class Bullet;
class EnemyMgr;
class GameOver;
class Particle;

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

	std::vector<Particle> parts1;
	std::vector<Particle> parts2;
	std::vector<Particle> *curParts;
	sf::Clock partsClock;
	void updateParts();
	void renderParts();
	void addParticles(ph::vec2f pos, ph::vec2f vel,
	                  int count, float spray=20, GLushort drop=255);

	EnemyMgr *enemies;

	void handleCollisions();

	sf::Clock clock;
	bool isGameOver;
	sf::Clock gameOverClock;
	void gameOver();
	GameOver *gameOverScreen;
};

#endif
