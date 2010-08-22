#include "enemy-manager.h"
#include "e-circle.h"

EnemyMgr::EnemyMgr()
	: list()
{
	list.push_back(new E_Circle(ph::vec2f(100, 100)));
}

void EnemyMgr::update () {
	for(std::vector<Enemy*>::iterator it = list.begin();
	    it != list.end(); it++)
	{
		if (! *it)
			continue;

		(*it)->update();
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
