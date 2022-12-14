#include <SFML/Graphics/Texture.hpp>
#include "TextureManager.h"
#include "Helpers.h"

TextureManager::TextureManager()
	: m_pPlayerShip			( nullptr )
	, m_pEnemyShip			( nullptr )
	, m_pPlayerBullet		( nullptr )
	, m_pEnemyBullet		( nullptr )
	, m_pBarrier			( nullptr )
	, m_pBackground			( nullptr )
	, m_pAmmoBarSegment		( nullptr )
	, m_pHealthBarSegment	( nullptr )
{
	loadPersistentTextures();
}

TextureManager::~TextureManager()
{
	unloadAllTextures();
}

bool TextureManager::load( const char* fileName, sf::Texture& textureToSet )
{
	bool loaded = textureToSet.loadFromFile( fileName );
	ASSERT( loaded == true );

	return loaded;
}

void TextureManager::loadTextures( GameState stateToLoad )
{
	switch( stateToLoad )
	{
		case GameState::Menu:
		{

		}
		break;
		case GameState::Game:
		{
			m_pPlayerShip = new sf::Texture;
			m_pEnemyShip = new sf::Texture;
			m_pPlayerBullet = new sf::Texture;
			m_pEnemyBullet = new sf::Texture;
			m_pBarrier = new sf::Texture;
			m_pAmmoBarSegment = new sf::Texture;
			m_pHealthBarSegment = new sf::Texture;

			load( "assets/player/ship.png", *m_pPlayerShip );
			load( "assets/enemy/enemy_one.png", *m_pEnemyShip );
			load( "assets/objects/player_bullet.png", *m_pPlayerBullet );
			load( "assets/objects/enemy_bullet.png", *m_pEnemyBullet );
			load( "assets/objects/barrier.png", *m_pBarrier );
			load( "assets/hud/ammo_bar_segment.png", *m_pAmmoBarSegment );
			load( "assets/hud/health_bar_segment.png", *m_pHealthBarSegment );
		}
		break;
	}
}

void TextureManager::unloadTextures( GameState stateToUnload )
{
	switch( stateToUnload )
	{
		case GameState::Menu:
		{
		}
		break;
		case GameState::Game:
		{
			safeDelete( m_pPlayerShip );
			safeDelete( m_pEnemyShip );
			safeDelete( m_pPlayerBullet );
			safeDelete( m_pEnemyBullet );
			safeDelete( m_pBarrier );
			safeDelete( m_pAmmoBarSegment );
			safeDelete( m_pHealthBarSegment );
		}
		break;
	}
}

void TextureManager::loadPersistentTextures()
{
	m_pBackground = new sf::Texture;

	load( "assets/background/background.png", *m_pBackground );
}

void TextureManager::unloadAllTextures()
{
	safeDelete( m_pPlayerShip );
	safeDelete( m_pEnemyShip );
	safeDelete( m_pPlayerBullet );
	safeDelete( m_pEnemyBullet );
	safeDelete( m_pBarrier );
	safeDelete( m_pBackground );
	safeDelete( m_pAmmoBarSegment );
	safeDelete( m_pHealthBarSegment );
}


const sf::Texture& TextureManager::getPlayerShip() const
{
	return *m_pPlayerShip;
}

const sf::Texture& TextureManager::getEnemyShip() const
{
	return *m_pEnemyShip;
}

const sf::Texture& TextureManager::getPlayerBullet() const
{
	return *m_pPlayerBullet;
}

const sf::Texture& TextureManager::getEnemyBullet() const
{
	return *m_pEnemyBullet;
}

const sf::Texture& TextureManager::getBarrier() const
{
	return *m_pBarrier;
}

const sf::Texture& TextureManager::getBackground() const
{
	return *m_pBackground;
}

const sf::Texture& TextureManager::getAmmoBarSegment() const
{
	return *m_pAmmoBarSegment;
}

const sf::Texture& TextureManager::getHealthBarSegment() const
{
	return *m_pHealthBarSegment;
}