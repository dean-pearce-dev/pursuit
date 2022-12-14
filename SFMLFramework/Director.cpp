#include <SFML/Graphics/RenderWindow.hpp>

#include "Director.h"
#include "BackgroundManager.h"
#include "BarrierManager.h"
#include "BulletManager.h"
#include "FontManager.h"
#include "GameplayDirector.h"
#include "HiScoreManager.h"
#include "InputManager.h"
#include "MainMenuManager.h"
#include "ReferenceManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "Helpers.h"

Director::Director()
	: m_pWindow				( nullptr )
	, m_pStateManager		( nullptr )
	, m_pTextureManager		( nullptr )
	, m_pMainMenuManager	( nullptr )
	, m_pBackgroundManager	( nullptr )
	, m_pBarrierManager		( nullptr )
	, m_pFontManager		( nullptr )
	, m_pHiScoreManager		( nullptr )
	, m_pInputManager		( nullptr )
	, m_pGameplayDirector	( nullptr )
	, m_pReferenceManager	( nullptr )
	, m_pSoundManager		( nullptr )
	, m_isPausePressed		( false )
{	
}

Director::~Director()
{
	safeDelete( m_pFontManager );
	safeDelete( m_pSoundManager );
	safeDelete( m_pReferenceManager );
	safeDelete( m_pGameplayDirector );
	safeDelete( m_pBarrierManager );
	safeDelete( m_pBackgroundManager );
	safeDelete( m_pMainMenuManager );
	safeDelete( m_pHiScoreManager );
	safeDelete( m_pInputManager );
	safeDelete( m_pTextureManager );
	safeDelete( m_pStateManager );
}

void Director::update( float deltaTime )
{
	switch( m_pStateManager->getState() )
	{
		// Menu state
		case GameState::Menu:
		{
			m_pBackgroundManager->update( deltaTime );
			m_pMainMenuManager->update( deltaTime );

			if( m_pMainMenuManager->shouldGameStart() )
			{
				changeState( GameState::Game );
				m_pStateManager->setInGameState( InGameState::Game );
			}
		}
		break;
		// Game state
		case GameState::Game:
		{
			m_pGameplayDirector->update( deltaTime );

			if( m_pGameplayDirector->shouldReturnToMenu() )
			{
				changeState( GameState::Menu );
			}
		}
		break;
	}
}

void Director::draw()
{
	switch( m_pStateManager->getState() )
	{
		case GameState::Menu:
		{
			m_pBackgroundManager->draw();
			m_pMainMenuManager->draw();
		}
		break;
		case GameState::Game:
		{
			m_pGameplayDirector->draw();
		}
		break;
	}
}

void Director::init( sf::RenderWindow& windowHandle )
{
	// Assigning the reference to the render window
	m_pWindow = &windowHandle;

	// Creating a state manager
	m_pStateManager = new StateManager();

	// Creating the texture manager
	m_pTextureManager = new TextureManager();

	// Creating the sound manager
	m_pSoundManager = new SoundManager();

	// Creating the input manager
	m_pInputManager = new InputManager();

	// Creating the font manager
	m_pFontManager = new FontManager();

	// Creating the reference manager
	m_pReferenceManager = new ReferenceManager();

	// Creating the background manager
	m_pBackgroundManager = new BackgroundManager();

	// Creating the main menu manager
	m_pMainMenuManager = new MainMenuManager();

	// Creating the hi score manager
	m_pHiScoreManager = new HiScoreManager();

	// Loading the main font into memory
	m_pFontManager->loadMainFont();

	// Loading textures and sound for the menu
	m_pTextureManager->loadTextures( GameState::Menu );
	m_pSoundManager->loadSounds( GameState::Menu );

	m_pHiScoreManager->init();

	m_pBackgroundManager->init( *this );
	m_pMainMenuManager->init( *this );

	m_pReferenceManager->initDirectorRefs( *this );
}

void Director::initState( GameState stateToInit )
{
	// Loading textures based on state before creating objects that require the textures
	m_pTextureManager->loadTextures( stateToInit );
	m_pSoundManager->loadSounds( stateToInit );

	switch( stateToInit )
	{
		case GameState::Menu:
		{
			m_pMainMenuManager = new MainMenuManager();
			

			m_pMainMenuManager->init( *this );
			m_pBackgroundManager->reset();

			m_pReferenceManager->initDirectorRefs( *this );
		}
		break;
		case GameState::Game:
		{
			m_pGameplayDirector = new GameplayDirector();

			m_pGameplayDirector->init( *m_pReferenceManager );
		}
		break;
	}
}

void Director::uninitState()
{
	switch( m_pStateManager->getState() )
	{
		case GameState::Menu:
		{
			safeDelete( m_pMainMenuManager );
		}
		break;
		case GameState::Game:
		{
			safeDelete( m_pGameplayDirector );
		}
		break;
	}

	// Unloading textures that were used during the state
	m_pTextureManager->unloadTextures( m_pStateManager->getState() );
	m_pSoundManager->unloadSounds( m_pStateManager->getState() );
}

void Director::changeState( const GameState stateToChange )
{
	uninitState();
	initState( stateToChange );
	m_pStateManager->setState( stateToChange );
}

sf::RenderWindow& Director::getWindowHandle()
{
	return *m_pWindow;
}

StateManager& Director::getStateManager()
{
	return *m_pStateManager;
}

TextureManager& Director::getTextureManager()
{
	return *m_pTextureManager;
}

MainMenuManager& Director::getMainMenuManager()
{
	return *m_pMainMenuManager;
}

BackgroundManager& Director::getBackgroundManager()
{
	return *m_pBackgroundManager;
}

BarrierManager& Director::getBarrierManager()
{
	return *m_pBarrierManager;
}

FontManager& Director::getFontManager()
{
	return *m_pFontManager;
}

HiScoreManager& Director::getHiScoreManager()
{
	return *m_pHiScoreManager;
}

InputManager& Director::getInputManager()
{
	return *m_pInputManager;
}

GameplayDirector& Director::getGameplayDirector()
{
	return *m_pGameplayDirector;
}

SoundManager& Director::getSoundManager()
{ 
	return *m_pSoundManager;
}