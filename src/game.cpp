#include "game.h"
#include "globals.h"
#include "player.h"
#include "bullet.h"
#include "enemy-manager.h"
#include "sound.h"
#include "gameover.h"

Game::Game()
	: player(new Player()),
	  bullets(),
	  enemies(new EnemyMgr()),
	  backdrop(),
	  isGameOver(false),
	  gameOverClock(),
	  gameOverScreen(NULL)
{
	backdrop.SetImage(G::Images::backdrop);
}

void Game::update() {
	if (isGameOver && gameOverClock.GetElapsedTime() >= 2) {
		G::gameScreen = NULL;
		G::curScreen = gameOverScreen;
		delete this;
		return;
	}

	handleEvents();

	if (player)
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

	if (player)
		player->render();

	for(std::vector<Bullet*>::iterator it = bullets.begin();
	    it != bullets.end(); it++)
	{
		if (! *it)
			continue;

		(*it)->render();
	}

	enemies->render();

	if (isGameOver) {
		int alpha = ph::min<int>(gameOverClock.GetElapsedTime() * 128,
		                         255);
		sf::Shape overlay
			= sf::Shape::Rectangle(0, 0, G::window.GetWidth(),
			                       G::window.GetHeight(),
			                       sf::Color(0, 0, 0, alpha));
		G::window.Draw(overlay);
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

void Game::gameOver() {
	isGameOver = true;
	gameOverClock.Reset();
	gameOverScreen = new GameOver(player->score, G::clock.GetElapsedTime());

	enemies->stopped = true; // halt production

	Sound::play(Sound::playerDeath);

	printf("Score: %d\n", player->score);

	delete player;
	player = NULL;
}
