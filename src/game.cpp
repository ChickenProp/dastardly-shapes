#include "game.h"

Game::Game()
	: player(new Player())
{}

void Game::update() {
	player->update();
}

void Game::render() {
	player->render();
}
