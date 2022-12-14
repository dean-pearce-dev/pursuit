#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>

#include "PauseManager.h"
#include "Director.h"
#include "FontManager.h"
#include "GameSound.h"
#include "GameText.h"
#include "GameplayDirector.h"
#include "Helpers.h"
#include "InputManager.h"
#include "ReferenceManager.h"
#include "StateManager.h"
#include "Settings.h"
#include "SoundManager.h"

PauseManager::PauseManager()
	: m_pWindow					( nullptr )
	, m_pPauseElementsArray		( nullptr )
	, m_pFontManager			( nullptr )
	, m_pInputManager			( nullptr )
	, m_pStateManager			( nullptr )
	, m_pSoundManager			( nullptr )
	, m_pGameplayDirector		( nullptr )
	, m_pSelectedElement		( nullptr )
	, m_pMenuMoveSound			( nullptr )
	, m_pMenuConfirmSound		( nullptr )
	, m_pMenuDenySound			( nullptr )
	, m_pOptionsElementsArray	( nullptr )
	, m_pauseState				( PauseState::Main )
	, m_selectedElementNum		( 0 )
	, m_animScale				( k_animDefaultScale )
	, m_animScaleDefault		( k_animDefaultScale )
	, m_animScaleSpeed			( k_animScaleSpeed )
	, m_animScaleOffset			( k_animScaleOffset )
	, m_animScaleIncrease		( false )
	, m_upIsPressed				( false )
	, m_downIsPressed			( false )
	, m_leftIsPressed			( false )
	, m_rightIsPressed			( false )
	, m_enterIsPressed			( true )
	, m_escIsPressed			( false )
	, m_shouldReturnToMenu		( false )
{

}

PauseManager::~PauseManager()
{
	safeDeleteArray( m_pPauseElementsArray );
	safeDeleteArray( m_pOptionsElementsArray );
	safeDelete( m_pMenuMoveSound );
	safeDelete( m_pMenuConfirmSound );
	safeDelete( m_pMenuDenySound );
}

void PauseManager::update( float deltaTime )
{
	switch( m_pStateManager->getInGameState() )
	{
		case InGameState::Game:
		{
			if( m_pInputManager->escIsPressed() && !m_escIsPressed )
			{
				m_pStateManager->setInGameState( InGameState::Pause );
				m_pGameplayDirector->pauseMusic();
				m_pMenuConfirmSound->play();
			}
		}
		break;
		case InGameState::Pause:
		{
			if( m_pauseState == PauseState::Main )
			{
				pausedUpdate( deltaTime );
			}
			else if( m_pauseState == PauseState::Options )
			{
				optionsUpdate( deltaTime );
			}
		}
		break;
	}

	m_escIsPressed = m_pInputManager->escIsPressed();
}

void PauseManager::draw()
{
	switch( m_pauseState )
	{
		case PauseState::Main:
		{
			for( int i = 0; i < k_pauseElementsNum; i++ )
			{
				m_pWindow->draw( m_pPauseElementsArray[i] );
			}
		}
		break;
		case PauseState::Options:
		{
			for( int i = 0; i < k_optionsElementsNum; i++ )
			{
				m_pWindow->draw( m_pOptionsElementsArray[i] );
			}
		}
		break;
	}
}

void PauseManager::init( const ReferenceManager& refManager )
{
	// Getting references to the window and the font manager
	m_pWindow = &refManager.getWindowHandle();
	m_pFontManager = &refManager.getFontManager();
	m_pInputManager = &refManager.getInputManager();
	m_pStateManager = &refManager.getStateManager();
	m_pGameplayDirector = &refManager.getGameplayDirector();
	m_pSoundManager = &refManager.getSoundManager();

	m_pMenuMoveSound = new GameSound();
	m_pMenuConfirmSound = new GameSound();
	m_pMenuDenySound = new GameSound();

	m_pMenuMoveSound->setBuffer( m_pSoundManager->getMenuMove() );
	m_pMenuConfirmSound->setBuffer( m_pSoundManager->getMenuConfirm() );
	m_pMenuDenySound->setBuffer( m_pSoundManager->getMenuDeny() );

	m_pMenuMoveSound->setVolume( m_pSoundManager->getFxVolume() );
	m_pMenuConfirmSound->setVolume( m_pSoundManager->getFxVolume() );
	m_pMenuDenySound->setVolume( m_pSoundManager->getFxVolume() );

	const sf::Font& font = m_pFontManager->getMainFont();

	// Setting up the array for the menu elements
	m_pPauseElementsArray = new GameText[k_pauseElementsNum];

	for( int i = 0; i < k_pauseElementsNum; i++ )
	{
		m_pPauseElementsArray[i].init( font, k_pauseElements[i] );
		m_pPauseElementsArray[i].setPosition( k_windowWidth / 2, k_pauseElementsYStart + ( k_pauseElementsYIncrement * i ) );
	}

	// Setting the selected menu element based on int
	m_pSelectedElement = &m_pPauseElementsArray[m_selectedElementNum];

	initOptionsScreen();
}

void PauseManager::pausedUpdate( float deltaTime )
{
	if( m_pInputManager->escIsPressed() && !m_escIsPressed )
	{
		m_pStateManager->setInGameState( InGameState::Game );
		m_pMenuDenySound->play();
		m_pGameplayDirector->playMusic();
	}

	if( m_pInputManager->downIsPressed() && !m_downIsPressed )
	{
		m_pPauseElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_selectedElementNum = ( m_selectedElementNum + 1 ) % k_pauseElementsNum;
		m_pMenuMoveSound->play();
	}

	if( m_pInputManager->upIsPressed() && !m_upIsPressed )
	{
		m_pPauseElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_selectedElementNum = ( ( k_pauseElementsNum - 1 ) + m_selectedElementNum ) % k_pauseElementsNum;
		m_pMenuMoveSound->play();
	}

	m_pSelectedElement = &m_pPauseElementsArray[m_selectedElementNum];

	selectedElementAnim( deltaTime );

	if( m_pInputManager->enterIsPressed() && !m_enterIsPressed )
	{
		switch( m_selectedElementNum )
		{
			// Resume
		case 0:
		{
			m_pStateManager->setInGameState( InGameState::Game );
			m_pGameplayDirector->playMusic();
		}
		break;
		// Restart
		case 1:
		{
			m_pGameplayDirector->resetGame();
			m_pStateManager->setInGameState( InGameState::Game );
		}
		break;
		// Options
		case 2:
		{
			m_pauseState = PauseState::Options;
			m_selectedElementNum = 0;
		}
		break;
		// Return to Menu
		case 3:
		{
			m_shouldReturnToMenu = true;
		}
		break;
		// Exit
		case 4:
		{
			m_pWindow->close();
		}
		break;
		}
		m_pMenuConfirmSound->play();
	}

	m_downIsPressed = m_pInputManager->downIsPressed();
	m_upIsPressed = m_pInputManager->upIsPressed();
	m_enterIsPressed = m_pInputManager->enterIsPressed();
}

void PauseManager::initOptionsScreen()
{
	const sf::Font& font = m_pFontManager->getMainFont();

	std::stringstream ss;

	m_pOptionsElementsArray = new GameText[k_optionsElementsNum];

	ss << k_optionsFxVolumeString << m_pSoundManager->getFxVolume();
	m_pOptionsElementsArray[0].init( font, ss.str(), k_pauseMenuElementsSize );
	m_pOptionsElementsArray[0].setPosition( k_windowWidth / 2, k_pauseElementsYStart );

	std::stringstream().swap( ss );

	ss << k_optionsMusicVolumeString << m_pSoundManager->getMusicVolume();
	m_pOptionsElementsArray[1].init( font, ss.str(), k_pauseMenuElementsSize );
	m_pOptionsElementsArray[1].setPosition( k_windowWidth / 2, k_pauseElementsYStart + k_pauseElementsYIncrement );

	m_pOptionsElementsArray[2].init( font, k_backString, k_pauseMenuElementsSize );
	m_pOptionsElementsArray[2].setPosition( k_windowWidth / 2, k_pauseElementsYStart + ( k_pauseElementsYIncrement * 2 ) );
}

void PauseManager::optionsUpdate( float deltaTime )
{
	float fxVolume = m_pSoundManager->getFxVolume();
	float musicVolume = m_pSoundManager->getMusicVolume();


	if( m_pInputManager->downIsPressed() && !m_downIsPressed )
	{
		m_pOptionsElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_selectedElementNum = ( m_selectedElementNum + 1 ) % k_optionsElementsNum;
		m_pMenuMoveSound->play();
	}
	if( m_pInputManager->upIsPressed() && !m_upIsPressed )
	{
		m_pOptionsElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_selectedElementNum = ( ( k_optionsElementsNum - 1 ) + m_selectedElementNum ) % k_optionsElementsNum;
		m_pMenuMoveSound->play();
	}
	if( m_pInputManager->leftIsPressed() && !m_leftIsPressed )
	{
		if( m_selectedElementNum == 0 )
		{
			fxVolume -= k_volumeIncrement;
			if( fxVolume < 0.0f )
			{
				fxVolume = 0.0f;
			}
			m_pSoundManager->setFxVolume( fxVolume );
		}
		else if( m_selectedElementNum == 1 )
		{
			musicVolume -= k_volumeIncrement;
			if( musicVolume < 0.0f )
			{
				musicVolume = 0.0f;
			}
			m_pSoundManager->setMusicVolume( musicVolume );
		}
		resetVolume();
		resetOptionStrings();
		m_pMenuMoveSound->play();
	}
	if( m_pInputManager->rightIsPressed() && !m_rightIsPressed )
	{
		if( m_selectedElementNum == 0 )
		{
			fxVolume += k_volumeIncrement;
			if( fxVolume > k_volumeMax )
			{
				fxVolume = k_volumeMax;
			}
			m_pSoundManager->setFxVolume( fxVolume );
		}
		else if( m_selectedElementNum == 1 )
		{
			musicVolume += k_volumeIncrement;
			if( musicVolume > k_volumeMax )
			{
				musicVolume = k_volumeMax;
			}
			m_pSoundManager->setMusicVolume( musicVolume );
		}
		resetVolume();
		resetOptionStrings();
		m_pMenuMoveSound->play();
	}
	if( m_pInputManager->enterIsPressed() && !m_enterIsPressed && m_selectedElementNum == k_optionsElementsNum - 1 )
	{
		m_pOptionsElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_pSoundManager->saveOptionsData();
		m_pauseState = PauseState::Main;
		m_selectedElementNum = 0;
		m_pMenuDenySound->play();
	}
	if( m_pInputManager->escIsPressed() && !m_escIsPressed )
	{
		m_pOptionsElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_pSoundManager->saveOptionsData();
		m_pauseState = PauseState::Main;
		m_selectedElementNum = 0;
		m_pMenuDenySound->play();
	}

	m_pSelectedElement = &m_pOptionsElementsArray[m_selectedElementNum];

	m_downIsPressed = m_pInputManager->downIsPressed();
	m_upIsPressed = m_pInputManager->upIsPressed();
	m_leftIsPressed = m_pInputManager->leftIsPressed();
	m_rightIsPressed = m_pInputManager->rightIsPressed();
	m_enterIsPressed = m_pInputManager->enterIsPressed();
	m_escIsPressed = m_pInputManager->escIsPressed();

	selectedElementAnim( deltaTime );
}

void PauseManager::resetVolume()
{
	m_pMenuConfirmSound->setVolume( m_pSoundManager->getFxVolume() );
	m_pMenuDenySound->setVolume( m_pSoundManager->getFxVolume() );
	m_pMenuMoveSound->setVolume( m_pSoundManager->getFxVolume() );
}

void PauseManager::resetOptionStrings()
{
	std::stringstream ss;

	ss << k_optionsFxVolumeString << m_pSoundManager->getFxVolume();
	m_pOptionsElementsArray[0].setString( ss.str() );

	std::stringstream().swap( ss );

	ss << k_optionsMusicVolumeString << m_pSoundManager->getMusicVolume();
	m_pOptionsElementsArray[1].setString( ss.str() );
}

void PauseManager::selectedElementAnim( float deltaTime )
{
	if( m_animScaleIncrease )
	{
		m_animScale += ( m_animScaleSpeed * deltaTime );
	}

	else if( !m_animScaleIncrease )
	{
		m_animScale -= ( m_animScaleSpeed * deltaTime );
	}

	if( m_animScale <= m_animScaleDefault - m_animScaleOffset )
	{
		m_animScale = m_animScaleDefault - m_animScaleOffset;
		m_animScaleIncrease = true;
	}

	else if( m_animScale > m_animScaleDefault + m_animScaleOffset )
	{
		m_animScale = m_animScaleDefault + m_animScaleOffset;
		m_animScaleIncrease = false;
	}
	m_pSelectedElement->setScale( m_animScale, m_animScale );
}

bool PauseManager::shouldReturnToMenu()
{
	return m_shouldReturnToMenu;
}