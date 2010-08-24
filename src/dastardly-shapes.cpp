#include "globals.h"
#include "includes.h"
#include "game.h"
#include "sound.h"

void handleEvents();
void handleEvent(sf::Event e);

int main (int argc, char **argv) {
	if (! G::loadImages())
		exit(1);
	Sound::loadSounds();

	G::window.Create(sf::VideoMode(570, 570, 32), "Dastardly Shapes");
	G::window.SetFramerateLimit(G::framerate);

	G::gameScreen = new Game();
	G::curScreen = G::gameScreen;
	
	G::curScreen->update();
	while (G::window.IsOpened()) {
		G::window.Clear();
		G::curScreen->render();
		G::window.Display();

		G::curScreen->update();		
	}
}
