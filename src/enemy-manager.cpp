#include "enemy-manager.h"
#include "e-circle.h"

EnemyMgr::EnemyMgr()
	: list()
{
	for (int i = 0; i < 100; i++)
		list.push_back(new E_Circle(ph::vec2f(100, 100)));

	numLiveEnemies = 100;
}

void EnemyMgr::enemyDied(Enemy *which) {
	numLiveEnemies--;
}

void EnemyMgr::update () {
	for(int i = 0; i < list.size(); i++) {
		if (! list[i])
			continue;

		if (list[i]->trash) {
			delete list[i];
			list[i] = NULL;
			continue;
		}

		list[i]->update();
	}
}

void EnemyMgr::render () {
	for(std::vector<Enemy*>::iterator it = list.begin();
	    it != list.end(); it++)
	{
		if (! *it)
			continue;

		(*it)->render();
	}
}
