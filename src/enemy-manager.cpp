#include "enemy-manager.h"
#include "globals.h"
#include "e-circle.h"
#include "e-triangle.h"
#include "e-square.h"
#include "sound.h"

EnemyMgr::EnemyMgr()
	: list(),
	  upcoming(),
	  glow(),
	  numLiveEnemies(0),
	  waveDifficulty(10),
	  waveClock(),
	  stopped(false)
{
	glow.SetImage(G::Images::glow);
	glow.SetCenter(64, 64);
	glow.Resize(30, 30);

	newWave();
}

void EnemyMgr::enemyDied(Enemy *which) {
	numLiveEnemies--;

	if (numLiveEnemies <= 0 && !unvivifiedWave)
		timeToWave = 0;
}

void EnemyMgr::update () {
	if (waveClock.GetElapsedTime() > timeToWave && !stopped)
		newWave();

	if (unvivifiedWave && waveClock.GetElapsedTime() >= 1)
		vivifyWave();

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

	if (!unvivifiedWave)
		return;

	for (int i = 0; i < upcoming.size(); i++) {
		glow.SetPosition(upcoming[i]->pos);
		float alpha = waveClock.GetElapsedTime() * 255;
		float size = 64 - waveClock.GetElapsedTime() * 35;
		glow.SetColor(sf::Color(255, 255, 255, alpha));
		glow.Resize(size, size);
		G::window.Draw(glow);
	}		
}

void EnemyMgr::newWave () {
	for (int i = 0; i < waveDifficulty; i++) {
		ph::vec2f pos = randomCornerPosition();

		Enemy *en = NULL;
		int type = ph::randi(ph::max(waveDifficulty/10, 1)) + 1;
		switch (type) {
		case 1: en = new E_Circle(pos); break;
		case 2: en = new E_Triangle(pos); break;
		case 3: default: en = new E_Square(pos); break;
		}

		upcoming.push_back(en);
		i += type;
	}

	unvivifiedWave = true;
	timeToWave = 20;
	waveClock.Reset();
	waveDifficulty += 5;
}

void EnemyMgr::vivifyWave () {
	for (int i = 0; i < upcoming.size(); i++)
		list.push_back(upcoming[i]);

	numLiveEnemies += upcoming.size();
	upcoming.clear();
	unvivifiedWave = false;

	Sound::play(Sound::newWave);
}

ph::vec2f EnemyMgr::randomCornerPosition () {
	float c = 50;
	ph::vec2f offset = ph::vec2f::polar(ph::randf(c), ph::randf(360));
	ph::vec2f corner( (ph::randi(2) ? c : G::window.GetWidth() - c),
	                  (ph::randi(2) ? c : G::window.GetHeight() - c) );

	return offset + corner;
}
