#include <fstream>

#include "SoundManager.h"
#include "Settings.h"
#include "Helpers.h"

SoundManager::SoundManager()
	: m_pFire			( nullptr )
	, m_pExplosion		( nullptr )
	, m_pLoseLife		( nullptr )
	, m_pGameOver		( nullptr )
	, m_pVictory		( nullptr )
	, m_pMenuMove		( nullptr )
	, m_pMenuConfirm	( nullptr )
	, m_pMenuDeny		( nullptr )
	, m_pMenuMusic		( nullptr )
	, m_pGameMusic		( nullptr )
	, m_fxVolume		( k_fxDefaultVolume )
	, m_musicVolume		( k_musicDefaultVolume )
{
	loadPersistentSounds();
	readOptionsData();
}

SoundManager::~SoundManager()
{
	unloadAllSounds();
}

bool SoundManager::load( const char* fileName, sf::SoundBuffer& bufferToSet )
{
	bool loaded = bufferToSet.loadFromFile( fileName );
	ASSERT( loaded == true );

	return loaded;
}

void SoundManager::loadSounds( GameState stateToLoad )
{
	switch( stateToLoad )
	{
		case GameState::Menu:
		{
			m_pMenuMusic = new sf::SoundBuffer;

			load( "assets/sound/music/menuMusic.wav", *m_pMenuMusic );
		}
		break;
		case GameState::Game:
		{
			m_pFire = new sf::SoundBuffer;
			m_pExplosion = new sf::SoundBuffer;
			m_pLoseLife = new sf::SoundBuffer;
			m_pGameOver = new sf::SoundBuffer;
			m_pVictory = new sf::SoundBuffer;

			m_pGameMusic = new sf::SoundBuffer;

			load( "assets/sound/fx/laserShot.wav", *m_pFire );
			load( "assets/sound/fx/explosion.wav", *m_pExplosion );
			load( "assets/sound/fx/loseLife.wav", *m_pLoseLife );
			load( "assets/sound/fx/gameOver.wav", *m_pGameOver );
			load( "assets/sound/fx/win.wav", *m_pVictory );
			load( "assets/sound/music/gameMusic.wav", *m_pGameMusic );
		}
		break;
	}
}

void SoundManager::unloadSounds( GameState stateToUnload )
{
	switch( stateToUnload )
	{
	case GameState::Menu:
	{
		safeDelete( m_pMenuMusic );
	}
	break;
	case GameState::Game:
	{
		safeDelete( m_pFire );
		safeDelete( m_pExplosion );
		safeDelete( m_pLoseLife );
		safeDelete( m_pGameOver );
		safeDelete( m_pVictory );
		safeDelete( m_pGameMusic );
	}
	break;
	}
}

void SoundManager::loadPersistentSounds()
{
	m_pMenuMove = new sf::SoundBuffer;
	m_pMenuConfirm = new sf::SoundBuffer;
	m_pMenuDeny = new sf::SoundBuffer;

	load( "assets/sound/fx/menuMove.wav", *m_pMenuMove );
	load( "assets/sound/fx/menuConfirm.wav", *m_pMenuConfirm );
	load( "assets/sound/fx/menuDeny.wav", *m_pMenuDeny );
}

void SoundManager::unloadAllSounds()
{
	safeDelete( m_pFire );
	safeDelete( m_pExplosion );
	safeDelete( m_pLoseLife );
	safeDelete( m_pGameOver );
	safeDelete( m_pVictory );
	safeDelete( m_pMenuMove );
	safeDelete( m_pMenuConfirm );
	safeDelete( m_pMenuDeny );
	safeDelete( m_pMenuMusic );
	safeDelete( m_pGameMusic );
}

float SoundManager::getFxVolume()
{
	return m_fxVolume;
}

void SoundManager::setFxVolume( float volume )
{
	m_fxVolume = volume;
}

float SoundManager::getMusicVolume()
{
	return m_musicVolume;
}

void SoundManager::setMusicVolume( float volume )
{
	m_musicVolume = volume;
}

void SoundManager::readOptionsData()
{
	std::ifstream optionsFile;
	optionsFile.open( "data/options.txt" );

	if( optionsFile.is_open() )
	{
		optionsFile >> m_fxVolume;
		optionsFile >> m_musicVolume;
	}
	else
	{
		saveOptionsData();
	}

	optionsFile.close();
}

void SoundManager::saveOptionsData()
{
	std::ofstream optionsFile;
	optionsFile.open( "data/options.txt" );

	if( optionsFile.is_open() )
	{
			optionsFile << static_cast<int>( m_fxVolume );
			optionsFile << "\n";
			optionsFile << static_cast< int >( m_musicVolume );
			optionsFile << "\n";
	}

	optionsFile.close();
}

const sf::SoundBuffer& SoundManager::getFire() const
{
	return *m_pFire;
}

const sf::SoundBuffer& SoundManager::getExplosion() const
{
	return *m_pExplosion;
}

const sf::SoundBuffer& SoundManager::getLoseLife() const
{
	return *m_pLoseLife;
}

const sf::SoundBuffer& SoundManager::getGameOver() const
{
	return *m_pGameOver;
}

const sf::SoundBuffer& SoundManager::getVictory() const
{
	return *m_pVictory;
}

const sf::SoundBuffer& SoundManager::getMenuMove() const
{
	return *m_pMenuMove;
}

const sf::SoundBuffer& SoundManager::getMenuConfirm() const
{
	return *m_pMenuConfirm;
}

const sf::SoundBuffer& SoundManager::getMenuDeny() const
{
	return *m_pMenuDeny;
}

const sf::SoundBuffer& SoundManager::getMenuMusic() const
{
	return *m_pMenuMusic;
}

const sf::SoundBuffer& SoundManager::getGameMusic() const
{
	return *m_pGameMusic;
}