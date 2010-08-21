#include "game.h"

Game::Game()
	: player(new Player()),
	  bullets(),
	  enemies(new EnemyMgr())
{
}

void Game::update() {
	handleEvents();

	player->update();

	for(std::vector<Bullet*>::iterator it = bullets.begin();
	    it != bullets.end(); it++)
	{
		if (! *it)
			continue;

		(*it)->update();
	}
}

void Game::render() {
	player->render();

	for(std::vector<Bullet*>::iterator it = bullets.begin();
	    it != bullets.end(); it++)
	{
		if (! *it)
			continue;

		(*it)->render();
	}
}

void Game::addBullet(Bullet *bullet) {
	bullets.push_back(bullet);
}

void Game::handleEvents() {
	sf::Event e;
	while (G::window.GetEvent(e))
		handleEvent(e);
}

void Game::handleEvent(sf::Event e) {
	switch(e.Type) {
	case sf::Event::Closed:
		G::window.Close();
		break;
	case sf::Event::KeyPressed:
		if (e.Key.Code == sf::Key::Escape)
			G::window.Close();
		break;
	}
}

