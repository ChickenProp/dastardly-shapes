#include "sound.h"

std::list<sf::Sound*> Sound::sounds;

sf::SoundBuffer *Sound::shoot;
sf::SoundBuffer *Sound::newWave;
sf::SoundBuffer *Sound::pickupEnemy;

void Sound::play(sf::SoundBuffer *buf, bool loop, float pitch, float vol) {
	if (!buf) return;

	sf::Sound *snd = new sf::Sound(*buf, loop, pitch, vol);
	snd->Play();
	sounds.push_front(snd);
}

#define LOADSOUND(var,file)					\
	var = new sf::SoundBuffer();				\
	if (!var->LoadFromFile("media/" file ".wav")) {		\
		delete var;					\
		var = NULL;					\
	}

void Sound::loadSounds () {
	LOADSOUND(shoot, "shoot");
	LOADSOUND(newWave, "new-wave");
	LOADSOUND(pickupEnemy, "pickup-enemy");
}
