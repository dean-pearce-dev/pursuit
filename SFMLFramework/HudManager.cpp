#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>

#include "HudManager.h"
#include "FontManager.h"
#include "GameSprite.h"
#include "GameText.h"
#include "Helpers.h"
#include "Player.h"
#include "ReferenceManager.h"
#include "Settings.h"
#include "TextureManager.h"

HudManager::HudManager()
	: m_pWindow			( nullptr )
	, m_pAmmoBarArray	( nullptr )
	, m_pLivesArray		( nullptr )
	, m_pScoreText		( nullptr )
	, m_pPlayer			( nullptr )
{

}

HudManager::~HudManager()
{
	safeDeleteArray( m_pAmmoBarArray );
	safeDeleteArray( m_pLivesArray );
	safeDelete( m_pScoreText );
}

void HudManager::update()
{
	ammoBarCheck();
	livesCheck();
	scoreCheck();
}

void HudManager::draw()
{
	for( int i = 0; i < k_playerMaxFiredBullets; i++ )
	{
		m_pWindow->draw( m_pAmmoBarArray[i] );
	}

	for( int i = 0; i < k_playerLives; i++ )
	{
		m_pWindow->draw( m_pLivesArray[i] );
	}
	m_pWindow->draw( *m_pScoreText );
}

void HudManager::init( ReferenceManager& refManager )
{
	m_pWindow = &refManager.getWindowHandle();
	m_pPlayer = &refManager.getPlayer();

	m_pAmmoBarArray = new GameSprite[ k_playerMaxFiredBullets ];
	m_pLivesArray = new GameSprite[ k_playerLives ];

	m_pScoreText = new GameText;

	std::stringstream ss;
	ss << k_scoreString << m_pPlayer->getScore();

	// Getting the font to use from the font manager, then using the string from settings.h
	const sf::Font& font = refManager.getFontManager().getMainFont();
	m_pScoreText->init( font, ss.str(), k_scoreStringSize, false );
	m_pScoreText->setPosition( k_scoreStringGapFromBorder, k_scoreStringGapFromBorder );

	for( int i = 0; i < k_playerMaxFiredBullets; i++ )
	{
		m_pAmmoBarArray[i].setCurrentTexture( refManager.getTextureManager().getAmmoBarSegment() );
		m_pAmmoBarArray[i].setScale( k_healthAmmoHudScale, k_healthAmmoHudScale );

		float width = m_pAmmoBarArray->getGlobalBounds().width;
		float height = m_pAmmoBarArray->getGlobalBounds().height;

		m_pAmmoBarArray[i].setPosition( sf::Vector2f( width / 2, k_arenaHeight - ( ( height * i )  + ( height / 2 ) ) ) );
	}

	for( int i = 0; i < k_playerLives; i++ )
	{
		m_pLivesArray[i].setCurrentTexture( refManager.getTextureManager().getHealthBarSegment() );
		m_pLivesArray[i].setScale( k_healthAmmoHudScale, k_healthAmmoHudScale );

		float width = m_pLivesArray->getGlobalBounds().width;
		float height = m_pLivesArray->getGlobalBounds().height;

		m_pLivesArray[i].setPosition( sf::Vector2f( k_arenaWidth - ( width / 2 ), k_arenaHeight - ( ( height * i ) + ( height / 2 ) ) ) );
	}
}

void HudManager::ammoBarCheck()
{
	for( int i = 0; i < k_playerMaxFiredBullets; i++ )
	{
		if( i < m_pPlayer->getRemainingBullets() )
		{
			m_pAmmoBarArray[i].setColor( k_healthAmmoDefaultColor );
		}
		else
		{
			m_pAmmoBarArray[i].setColor( k_healthAmmoDepletedColor );
		}
	}
}

void HudManager::livesCheck()
{
	for( int i = 0; i < k_playerLives; i++ )
	{
		if( i < m_pPlayer->getLives() )
		{
			m_pLivesArray[i].setColor( k_healthAmmoDefaultColor );
		}
		else
		{
			m_pLivesArray[i].setColor( k_healthAmmoDepletedColor );
		}
	}
}

void HudManager::scoreCheck()
{
	std::stringstream ss;
	ss << k_scoreString << m_pPlayer->getScore();
	m_pScoreText->setString( ss.str() );
}