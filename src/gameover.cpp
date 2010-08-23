#include "gameover.h"
#include "globals.h"
#include "game.h"

GameOver::GameOver (int score, float time) {
	char text[100];
	sprintf(text,
	        "Score: %d\n"
	        "Time: %d\n"
	        "Any key to play again\n"
	        "Esc to quit",
	        score, (int) time);

	string.SetFont(sf::Font::GetDefaultFont());
	string.SetText(text);
	string.SetPosition(200, 200);
}

void GameOver::render () {
	G::window.Draw(string);
}

void GameOver::update () {
	sf::Event e;
	while (G::window.GetEvent(e))
		handleEvent(e);
}

void GameOver::handleEvent(sf::Event e) {
	switch(e.Type) {
	case sf::Event::Closed:
		G::window.Close();
		break;
	case sf::Event::KeyPressed:
		if (e.Key.Code == sf::Key::Escape)
			G::window.Close();
		else
			newGame();
		break;
	}
}

void GameOver::newGame () {
	G::gameScreen = new Game();
	G::curScreen = G::gameScreen;
	delete this;
}
