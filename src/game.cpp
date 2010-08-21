#include "game.h"

Game::Game()
	: player(new Player()),
	  bullet(new Bullet(ph::vec2f(320, 200), ph::vec2f(0.01, 0.02)))  
{}

void Game::update() {
	handleEvents();

	player->update();
	bullet->update();
}

void Game::render() {
	player->render();
	bullet->render();
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

