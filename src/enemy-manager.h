#ifndef GW_ENEMY_MANAGER_H
#define GW_ENEMY_MANAGER_H

#include "includes.h"
#include "enemy.h"

class EnemyMgr {
public:
	EnemyMgr();

	std::vector<Enemy*> list;

	void update();
	void render();

	void enemyDied(Enemy *which);
	int numLiveEnemies;

	void newWave();
	float timeToWave;
	sf::Clock waveClock;
	int waveCount;

	ph::vec2f randomCornerPosition();
};

#endif
