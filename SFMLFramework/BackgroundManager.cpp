#include <SFML/Graphics/RenderWindow.hpp>

#include "BackgroundManager.h"
#include "Background.h"
#include "Director.h"
#include "TextureManager.h"
#include "Helpers.h"
#include "Settings.h"

BackgroundManager::BackgroundManager()
	: m_pWindow			( nullptr )
	, m_pTextureManager ( nullptr )
	, m_speed			( k_bgSpeed )
	, m_pBackground1	( nullptr )
	, m_pBackground2	( nullptr )
{
}

BackgroundManager::~BackgroundManager()
{
	// Safe deleting pointers
	safeDelete( m_pBackground1 );
	safeDelete( m_pBackground2 );
}

void BackgroundManager::update( float deltaTime )
{
	m_pBackground1->update( deltaTime );
	m_pBackground2->update( deltaTime );
}

void BackgroundManager::draw()
{
	m_pBackground1->draw();
	m_pBackground2->draw();
}

void BackgroundManager::init( Director& director )
{
	// Getting references
	m_pWindow = &director.getWindowHandle();
	m_pTextureManager = &director.getTextureManager();

	// Creating the backgrounds
	m_pBackground1 = new Background();
	m_pBackground2 = new Background();

	m_pBackground1->init( *m_pWindow, m_pTextureManager->getBackground() );
	m_pBackground2->init( *m_pWindow, m_pTextureManager->getBackground() );

	m_pBackground2->setPosition( k_arenaWidth / 2, m_pBackground2->getGlobalBounds().height / 2 - k_arenaHeight );
}

void BackgroundManager::reset()
{
	sf::Vector2f posToSet = sf::Vector2f( k_arenaWidth / 2, m_pBackground2->getGlobalBounds().height / 2 - k_arenaHeight );
	m_pBackground2->setPosition( posToSet );
	posToSet.y += m_pBackground1->getGlobalBounds().height;
	m_pBackground1->setPosition( posToSet );
}