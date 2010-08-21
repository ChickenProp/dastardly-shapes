#include "game.h"

Game::Game()
	: player(new Player()),
	  bullet(new Bullet(ph::vec2f(320, 200), ph::vec2f(0.01, 0.02)))  
{}

void Game::update() {
	player->update();
	bullet->update();
}

void Game::render() {
	player->render();
	bullet->render();
}
