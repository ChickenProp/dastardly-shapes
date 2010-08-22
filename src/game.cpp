#include "game.h"

Game::Game()
	: player(new Player()),
	  bullets(),
	  enemies(new EnemyMgr()),
	  backdrop()
{
	backdrop.SetImage(G::Images::backdrop);
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

	enemies->update();

	handleCollisions();

	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i] && bullets[i]->trash) {
			delete bullets[i];
			bullets[i] = 0;
		}
	}
}

void Game::render() {
	G::window.Draw(backdrop);

	player->render();

	for(std::vector<Bullet*>::iterator it = bullets.begin();
	    it != bullets.end(); it++)
	{
		if (! *it)
			continue;

		(*it)->render();
	}

	enemies->render();
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

void Game::handleCollisions() {
	for(std::vector<Enemy*>::iterator it = enemies->list.begin();
	    it != enemies->list.end(); it++)
	{
		if (Entity::deadPtr(*it))
			continue;

		if ((*it)->colliding(player))
			player->hitEnemy(*it);

		if ((*it)->dead)
			continue;

		(*it)->checkBulletCollisions(bullets);
	}
}
