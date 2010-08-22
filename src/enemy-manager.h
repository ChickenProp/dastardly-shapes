#ifndef GW_ENEMY_MANAGER_H
#define GW_ENEMY_MANAGER_H

#include "includes.h"
#include "enemy.h"

class EnemyMgr {
public:
	EnemyMgr();

	std::vector<Enemy*> list;

	sf::Sprite glow;
	std::vector<Enemy*> upcoming;

	void update();
	void render();

	void enemyDied(Enemy *which);
	int numLiveEnemies;

	void newWave();
	void vivifyWave();
	bool unvivifiedWave;
	float timeToWave;
	sf::Clock waveClock;
	int waveDifficulty;

	ph::vec2f randomCornerPosition();
};

#endif
