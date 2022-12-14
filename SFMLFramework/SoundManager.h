#ifndef	SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "GameState.h"
#include <SFML/Audio/SoundBuffer.hpp>

class SoundManager
{
private:
	sf::SoundBuffer* m_pFire;
	sf::SoundBuffer* m_pExplosion;
	sf::SoundBuffer* m_pLoseLife;
	sf::SoundBuffer* m_pGameOver;
	sf::SoundBuffer* m_pVictory;
	sf::SoundBuffer* m_pMenuMove;
	sf::SoundBuffer* m_pMenuConfirm;
	sf::SoundBuffer* m_pMenuDeny;

	sf::SoundBuffer* m_pMenuMusic;
	sf::SoundBuffer* m_pGameMusic;

	float m_fxVolume;
	float m_musicVolume;

public:
	SoundManager();

	~SoundManager();

	bool load( const char* fileName, sf::SoundBuffer& bufferToSet );

	void loadSounds( GameState stateToLoad );
	void unloadSounds( GameState stateToUnload );

	void loadPersistentSounds();

	void unloadAllSounds();

	float getFxVolume();
	void setFxVolume( float volume );
	float getMusicVolume();
	void setMusicVolume( float volume );

	void readOptionsData();
	void saveOptionsData();


	const sf::SoundBuffer& getFire() const;
	const sf::SoundBuffer& getExplosion() const;
	const sf::SoundBuffer& getLoseLife() const;
	const sf::SoundBuffer& getGameOver() const;
	const sf::SoundBuffer& getVictory() const;
	const sf::SoundBuffer& getMenuMove() const;
	const sf::SoundBuffer& getMenuConfirm() const;
	const sf::SoundBuffer& getMenuDeny() const;
	const sf::SoundBuffer& getMenuMusic() const;
	const sf::SoundBuffer& getGameMusic() const;
};

#endif // End of '#ifndef SOUNDMANAGER_H'