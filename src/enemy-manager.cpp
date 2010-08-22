#include "enemy-manager.h"
#include "globals.h"
#include "e-circle.h"
#include "sound.h"

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
	for (int i = 0; i < 20; i++)
		list.push_back(new E_Circle(randomCornerPosition()));

	numLiveEnemies += 20;
	timeToWave = 10;
	waveClock.Reset();

	Sound::play(Sound::newWave);
}

ph::vec2f EnemyMgr::randomCornerPosition () {
	float c = 50;
	ph::vec2f offset = ph::vec2f::polar(ph::randf(c), ph::randf(360));
	ph::vec2f corner( (ph::randi(2) ? c : G::window.GetWidth() - c),
	                  (ph::randi(2) ? c : G::window.GetHeight() - c) );

	return offset + corner;
}
