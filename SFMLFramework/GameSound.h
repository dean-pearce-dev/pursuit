#ifndef GAMESOUND
#define GAMESOUND

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class GameSound : public sf::Sound
{
private:

public:
	GameSound();
	~GameSound();
};

#endif