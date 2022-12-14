#include <SFML/Graphics/RenderWindow.hpp>

#include "Credits.h"
#include "Director.h"
#include "ReferenceManager.h"
#include "FontManager.h"
#include "GameText.h"
#include "Helpers.h"
#include "Settings.h"

Credits::Credits()
	: m_pWindow				( nullptr )
	, m_pDevelopedText		( nullptr )
	, m_pNameText			( nullptr )
	, m_pMusicByText		( nullptr )
	, m_pMenuMusicText		( nullptr )
	, m_pGameMusicText		( nullptr )
	, m_pEffectsFromText	( nullptr )
	, m_pZapsplatText		( nullptr )
	, m_pFontFromText		( nullptr )
	, m_pFontText			( nullptr )
	, m_gameTextArray		( k_creditsElementsNum )
	, m_scrollSpeed			( k_creditsScrollSpeed )
{

}

Credits::~Credits()
{
	safeDelete( m_pDevelopedText );
	safeDelete( m_pNameText );
	safeDelete( m_pMusicByText );
	safeDelete( m_pMenuMusicText );
	safeDelete( m_pGameMusicText );
	safeDelete( m_pEffectsFromText );
	safeDelete( m_pZapsplatText );
	safeDelete( m_pFontFromText );
	safeDelete( m_pFontText );
}

void Credits::update( float deltaTime )
{
	sf::Vector2f tempPos;

	for( int i = 0; i < k_creditsElementsNum; i++ )
	{
		tempPos = m_gameTextArray[i]->getPosition();
		tempPos.y -= k_creditsScrollSpeed * deltaTime;
		m_gameTextArray[i]->setPosition( tempPos );
	}
}

void Credits::draw()
{
	for( int i = 0; i < k_creditsElementsNum; i++ )
	{
		m_pWindow->draw( *m_gameTextArray[i] );
	}
}

void Credits::init( Director& director )
{
	m_pWindow = &director.getWindowHandle();

	const sf::Font& font = director.getFontManager().getMainFont();

	m_pDevelopedText = new GameText();
	m_pNameText = new GameText();
	m_pMusicByText = new GameText();
	m_pMenuMusicText = new GameText();
	m_pGameMusicText = new GameText();
	m_pEffectsFromText = new GameText();
	m_pZapsplatText = new GameText();
	m_pFontFromText = new GameText();
	m_pFontText = new GameText();

	m_gameTextArray[0] = m_pDevelopedText;
	m_gameTextArray[1] = m_pNameText;
	m_gameTextArray[2] = m_pMusicByText;
	m_gameTextArray[3] = m_pMenuMusicText;
	m_gameTextArray[4] = m_pGameMusicText;
	m_gameTextArray[5] = m_pEffectsFromText;
	m_gameTextArray[6] = m_pZapsplatText;
	m_gameTextArray[7] = m_pFontFromText;
	m_gameTextArray[8] = m_pFontText;

	sf::Vector2f tempPos;

	m_pDevelopedText->init( font, k_creditsDevString, k_creditsHeaderSize );
	m_pDevelopedText->setPosition( k_windowWidth / 2, k_windowHeight + k_creditsGap );

	tempPos = m_pDevelopedText->getPosition();
	tempPos.y += k_creditsSubGap;

	m_pNameText->init( font, k_creditsNameString, k_creditsSubHeaderSize );
	m_pNameText->setPosition( tempPos );

	tempPos.y += k_creditsGap;

	m_pMusicByText->init( font, k_creditsMusicString, k_creditsHeaderSize );
	m_pMusicByText->setPosition( tempPos );

	tempPos.y += k_creditsSubGap;

	m_pMenuMusicText->init( font, k_creditsMenuMusic, k_creditsSubHeaderSize );
	m_pMenuMusicText->setPosition( tempPos );

	tempPos.y += k_creditsSubGap;

	m_pGameMusicText->init( font, k_creditsGameMusic, k_creditsSubHeaderSize );
	m_pGameMusicText->setPosition( tempPos );

	tempPos.y += k_creditsGap;

	m_pEffectsFromText->init( font, k_creditsFxString, k_creditsHeaderSize );
	m_pEffectsFromText->setPosition( tempPos );

	tempPos.y += k_creditsSubGap;

	m_pZapsplatText->init( font, k_creditsZapsplatString, k_creditsSubHeaderSize );
	m_pZapsplatText->setPosition( tempPos );

	tempPos.y += k_creditsGap;

	m_pFontFromText->init( font, k_creditsFontString, k_creditsHeaderSize );
	m_pFontFromText->setPosition( tempPos );

	tempPos.y += k_creditsSubGap;

	m_pFontText->init( font, k_creditsFreeFontString, k_creditsSubHeaderSize );
	m_pFontText->setPosition( tempPos );

}

void Credits::reinitPos()
{
	sf::Vector2f tempPos;

	m_pDevelopedText->setPosition( k_windowWidth / 2, k_windowHeight + k_creditsGap );

	tempPos = m_pDevelopedText->getPosition();
	tempPos.y += k_creditsSubGap;

	m_pNameText->setPosition( tempPos );
	tempPos.y += k_creditsGap;

	m_pMusicByText->setPosition( tempPos );
	tempPos.y += k_creditsSubGap;

	m_pMenuMusicText->setPosition( tempPos );
	tempPos.y += k_creditsSubGap;

	m_pGameMusicText->setPosition( tempPos );
	tempPos.y += k_creditsGap;

	m_pEffectsFromText->setPosition( tempPos );
	tempPos.y += k_creditsSubGap;

	m_pZapsplatText->setPosition( tempPos );
	tempPos.y += k_creditsGap;

	m_pFontFromText->setPosition( tempPos );
	tempPos.y += k_creditsSubGap;

	m_pFontText->setPosition( tempPos );
}

bool Credits::creditsFinished()
{
	return m_pFontText->getPosition().y < -( m_pFontText->getLocalBounds().height / 2 );
}