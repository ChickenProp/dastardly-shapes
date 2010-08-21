#ifndef GW_ENEMY_MANAGER_H
#define GW_ENEMY_MANAGER_H

#include "includes.h"
#include "enemy.h"

class EnemyMgr {
public:
	EnemyMgr();

	std::vector<Enemy*> enemies;

	void update();
	void render();
};

#endif
