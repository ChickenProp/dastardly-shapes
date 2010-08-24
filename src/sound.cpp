#include "sound.h"

std::list<sf::Sound*> Sound::sounds;

sf::SoundBuffer *Sound::shoot;
sf::SoundBuffer *Sound::bounce;
sf::SoundBuffer *Sound::newWave;
sf::SoundBuffer *Sound::pickupEnemy;
sf::SoundBuffer *Sound::enemyHit;
sf::SoundBuffer *Sound::enemyKill;
sf::SoundBuffer *Sound::playerDeath;

bool isStopped(sf::Sound *snd) {
	return snd->GetStatus() == sf::Sound::Stopped;
}

void Sound::play(sf::SoundBuffer *buf, bool loop, float pitch, float vol) {
	if (!buf) return;

	sf::Sound *snd = new sf::Sound(*buf, loop, pitch, vol);
	snd->Play();
	sounds.push_front(snd);

	sounds.remove_if(&isStopped);
}

#define LOADSOUND(var,file)					\
	var = new sf::SoundBuffer();				\
	if (!var->LoadFromFile("media/" file ".wav")) {		\
		delete var;					\
		var = NULL;					\
	}

void Sound::loadSounds () {
	LOADSOUND(shoot, "shoot");
	LOADSOUND(bounce, "bounce");
	LOADSOUND(newWave, "new-wave");
	LOADSOUND(pickupEnemy, "pickup-enemy");
	LOADSOUND(enemyHit, "enemy-hit");
	LOADSOUND(enemyKill, "enemy-kill");
	LOADSOUND(playerDeath, "player-death");	
}
