#include "globals.h"
#include "includes.h"
#include "game.h"

void handleEvents();
void handleEvent(sf::Event e);

int main (int argc, char **argv) {
	G::window.Create(sf::VideoMode(640, 480, 32), "GW");

	G::gameScreen = new Game();
	G::curScreen = G::gameScreen;

	while (G::window.IsOpened()) {
		G::curScreen->update();

		G::window.Clear();
		G::curScreen->render();
		G::window.Display();

		handleEvents();
	}
}

void handleEvents () {
	sf::Event e;
	while (G::window.GetEvent(e))
		handleEvent(e);
}

void handleEvent(sf::Event e) {
	switch(e.Type) {
	case sf::Event::Closed:
		G::window.Close();
		break;
	}
}
