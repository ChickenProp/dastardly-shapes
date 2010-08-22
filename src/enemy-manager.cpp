#include "enemy-manager.h"
#include "e-circle.h"

EnemyMgr::EnemyMgr()
	: list(),
	  numLiveEnemies(0),
	  waveCount(0),
	  waveClock()
{
	newWave();
}

void EnemyMgr::enemyDied(Enemy *which) {
	numLiveEnemies--;

	if (numLiveEnemies <= 0)
		timeToWave = 0;
}

void EnemyMgr::update () {
	if (waveClock.GetElapsedTime() > timeToWave)
		newWave();

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

void EnemyMgr::newWave () {
	for (int i = 0; i < 100; i++)
		list.push_back(new E_Circle(ph::vec2f(100, 100)));

	numLiveEnemies += 100;
	timeToWave = 10;
	waveClock.Reset();
}
