#include "game.h"
#include "globals.h"
#include "player.h"
#include "bullet.h"
#include "enemy-manager.h"
#include "sound.h"
#include "gameover.h"
#include "particle.h"

Game::Game()
	: player(new Player()),
	  bullets(),
	  enemies(new EnemyMgr()),
	  backdrop(),
	  clock(),
	  isGameOver(false),
	  gameOverClock(),
	  gameOverScreen(NULL),
	  parts1(),
	  parts2(),
	  curParts(&parts1)
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

	updateParts();
}

void Game::updateParts () {
	for (int i = 0; i < parts1.size(); i++)
		parts1[i].update();

	for (int i = 0; i < parts2.size(); i++)
		parts2[i].update();

	if (partsClock.GetElapsedTime() >= 5) {
		curParts = (curParts == &parts1 ? &parts2 : &parts1);
		curParts->clear();
		partsClock.Reset();
	}
}

void Game::addParticles(ph::vec2f pos, ph::vec2f vel, int count,
                        float spray, GLushort drop)
{
	float r = vel.length();
	if (r == 0)
		return;
	float thetamin = vel.angle() - spray/2;

	for (int i = 0; i < count; i++) {
		float d = ph::randf(2*r);
		float t = ph::randf(spray) + thetamin;

		curParts->push_back(Particle(pos, ph::vec2f::polar(d, t),
		                             drop));
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

	renderParts();

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

void Game::renderParts () {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 570, 570, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	int stride = sizeof(Particle);

	glVertexPointer(2, GL_FLOAT, stride, &parts1[0].pos);
	glColorPointer(4, GL_UNSIGNED_SHORT, stride, &parts1[0].r);
	glDrawArrays(GL_POINTS, 0, parts1.size());	

	glVertexPointer(2, GL_FLOAT, stride, &parts2[0].pos);
	glColorPointer(4, GL_UNSIGNED_SHORT, stride, &parts2[0].r);
	glDrawArrays(GL_POINTS, 0, parts2.size());	
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
	gameOverScreen = new GameOver(player->score, clock.GetElapsedTime());

	enemies->stopped = true; // halt production

	Sound::play(Sound::playerDeath);

	printf("Score: %d\n", player->score);

	delete player;
	player = NULL;
}
