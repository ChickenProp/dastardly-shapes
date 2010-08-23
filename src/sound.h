#ifndef GW_SOUND_H
#define GW_SOUND_H

#include "includes.h"

class Sound {
public:
	static void play(sf::SoundBuffer* buf,
	                 bool loop=false, float pitch=1.0f, float vol=100.0f);
	static void loadSounds();
	static std::list<sf::Sound*> sounds;

	static sf::SoundBuffer *shoot;
	static sf::SoundBuffer *bounce;
	static sf::SoundBuffer *newWave;
	static sf::SoundBuffer *pickupEnemy;
	static sf::SoundBuffer *enemyHit;
	static sf::SoundBuffer *enemyKill;
	static sf::SoundBuffer *playerDeath;
};

#endif
