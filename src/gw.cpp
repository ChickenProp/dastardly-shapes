#include "globals.h"
#include "includes.h"

void handleEvents();
void handleEvent(sf::Event e);

int main (int argc, char **argv) {
	G::window.Create(sf::VideoMode(640, 480, 32), "GW");
	while (G::window.IsOpened()) {
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
