#include "enemy-manager.h"
#include "e-circle.h"

EnemyMgr::EnemyMgr()
	: enemies()
{
	enemies.push_back(new E_Circle(ph::vec2f(100, 100)));
}

void EnemyMgr::update () {
	for(std::vector<Enemy*>::iterator it = enemies.begin();
	    it != enemies.end(); it++)
	{
		if (! *it)
			continue;

		(*it)->update();
	}
}

void EnemyMgr::render () {
	for(std::vector<Enemy*>::iterator it = enemies.begin();
	    it != enemies.end(); it++)
	{
		if (! *it)
			continue;

		(*it)->render();
	}
}
