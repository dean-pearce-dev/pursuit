#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>

#include "Director.h"
#include "Credits.h"
#include "MainMenuManager.h"
#include "GameSound.h"
#include "GameText.h"
#include "Helpers.h"
#include "HiScore.h"
#include "HiScoreManager.h"
#include "InputManager.h"
#include "FontManager.h"
#include "Settings.h"
#include "SoundManager.h"

MainMenuManager::MainMenuManager()
	:	m_pWindow				( nullptr )
	,	m_pMenuElementsArray	( nullptr )
	,	m_pFontManager			( nullptr )
	,	m_pHiScoreManager		( nullptr )
	,	m_pInputManager			( nullptr )
	,	m_pSoundManager			( nullptr )
	,	m_pSelectedElement		( nullptr )
	,	m_pFxVolumeText			( nullptr )
	,	m_pMusicVolumeText		( nullptr )
	,	m_pBackText				( nullptr )
	,	m_pHighScoresText		( nullptr )
	,	m_pInitialsArray		( nullptr )
	,	m_pScoresArray			( nullptr )
	,	m_pOptionsElementsArray	( nullptr )
	,	m_pMenuMoveSound		( nullptr )
	,	m_pMenuConfirmSound		( nullptr )
	,	m_pMenuDenySound		( nullptr )
	,	m_pMenuMusic			( nullptr )
	,	m_pCredits				( nullptr )
	,	m_menuState				( MenuState::Main )
	,	m_selectedElementNum	( 0 )
	,	m_animScale				( k_animDefaultScale )
	,	m_animScaleDefault		( k_animDefaultScale )
	,	m_animScaleSpeed		( k_animScaleSpeed )
	,	m_animScaleOffset		( k_animScaleOffset )
	,	m_animScaleIncrease		( false )
	,	m_upIsPressed			( false )
	,	m_downIsPressed			( false )
	,	m_leftIsPressed			( false )
	,	m_rightIsPressed		( false )
	,	m_enterIsPressed		( true )
	,	m_escIsPressed			( false )
	,	m_shouldGameStart		( false )
{
}

MainMenuManager::~MainMenuManager()
{
	safeDeleteArray( m_pMenuElementsArray );
	safeDeleteArray( m_pInitialsArray );
	safeDeleteArray( m_pScoresArray );
	safeDelete( m_pMenuMoveSound );
	safeDelete( m_pMenuConfirmSound );
	safeDelete( m_pMenuDenySound );
	safeDelete( m_pMenuMusic );
	safeDelete( m_pFxVolumeText );
	safeDelete( m_pMusicVolumeText );
	safeDelete( m_pBackText );
	safeDelete( m_pHighScoresText );
	safeDelete( m_pCredits );
	safeDeleteArray( m_pOptionsElementsArray);
}

void MainMenuManager::update( float deltaTime )
{
	switch( m_menuState )
	{
		case MenuState::Main:
		{
			menuUpdate( deltaTime );
		}
		break;
		case MenuState::Leaderboard:
		{
			leaderboardUpdate( deltaTime );
		}
		break;
		case MenuState::Options:
		{
			optionsUpdate( deltaTime );
		}
		break;
		case MenuState::Credits:
		{
			m_pCredits->update( deltaTime );

			if( m_pInputManager->escIsPressed() || m_pInputManager->enterIsPressed() && !m_enterIsPressed || m_pCredits->creditsFinished() )
			{
				m_menuState = MenuState::Main;
				m_pMenuDenySound->play();
			}

			m_enterIsPressed = m_pInputManager->enterIsPressed();
		}
		break;
	}
}

void MainMenuManager::draw()
{
	switch( m_menuState )
	{
		case MenuState::Main:
		{
			for( int i = 0; i < k_menuElementsNum; i++ )
			{
				m_pWindow->draw( m_pMenuElementsArray[i] );
			}
		}
		break;
		case MenuState::Leaderboard:
		{
			m_pWindow->draw( *m_pHighScoresText );
			m_pWindow->draw( *m_pBackText );

			for( int i = 0; i < k_savedHighScoresNum; i++ )
			{
				m_pWindow->draw( m_pInitialsArray[i] );
				m_pWindow->draw( m_pScoresArray[i] );
			}
		}
		break;
		case MenuState::Options:
		{
			for( int i = 0; i < k_optionsElementsNum; i++ )
			{
				m_pWindow->draw( m_pOptionsElementsArray[i] );
			}
		}
		break;
		case MenuState::Credits:
		{
			m_pCredits->draw();
		}
		break;
	}

}

void MainMenuManager::init( Director& director )
{
	// Getting references to the window and the font manager
	m_pWindow = &director.getWindowHandle();
	m_pFontManager = &director.getFontManager();
	m_pInputManager = &director.getInputManager();
	m_pSoundManager = &director.getSoundManager();
	m_pHiScoreManager = &director.getHiScoreManager();

	m_pCredits = new Credits();
	m_pCredits->init( director );

	initMenuScreen();
	initLeaderboardScreen();
	initOptionsScreen();

	// Setting the selected menu element based on int
	m_pSelectedElement = &m_pMenuElementsArray[m_selectedElementNum];

	m_pMenuMusic->setLoop( true );
	m_pMenuMusic->play();
}

void MainMenuManager::initMenuScreen()
{
	m_pMenuMoveSound = new GameSound();
	m_pMenuConfirmSound = new GameSound();
	m_pMenuDenySound = new GameSound();
	m_pMenuMusic = new GameSound();

	m_pMenuMoveSound->setBuffer( m_pSoundManager->getMenuMove() );
	m_pMenuConfirmSound->setBuffer( m_pSoundManager->getMenuConfirm() );
	m_pMenuDenySound->setBuffer( m_pSoundManager->getMenuDeny() );
	m_pMenuMusic->setBuffer( m_pSoundManager->getMenuMusic() );

	m_pMenuMoveSound->setVolume( m_pSoundManager->getFxVolume() );
	m_pMenuConfirmSound->setVolume( m_pSoundManager->getFxVolume() );
	m_pMenuDenySound->setVolume( m_pSoundManager->getFxVolume() );
	m_pMenuMusic->setVolume( m_pSoundManager->getMusicVolume() );

	// Setting up the array for the menu elements
	m_pMenuElementsArray = new GameText[k_menuElementsNum];

	const sf::Font& font = m_pFontManager->getMainFont();

	for( int i = 0; i < k_menuElementsNum; i++ )
	{
		m_pMenuElementsArray[i].init( font, k_menuElements[i] );
		m_pMenuElementsArray[i].setPosition( k_windowWidth / 2, k_menuElementsYStart + ( k_menuElementsYIncrement * i ) );
	}
}

void MainMenuManager::initLeaderboardScreen()
{
	m_pInitialsArray = new GameText[k_savedHighScoresNum];
	m_pScoresArray = new GameText[k_savedHighScoresNum];
	m_pHighScoresText = new GameText;
	m_pBackText = new GameText;

	std::stringstream ss;

	const sf::Font& font = m_pFontManager->getMainFont();

	m_pHighScoresText->init( font, k_highScoreString, k_highScoreStringSize );
	m_pHighScoresText->setPosition( k_windowWidth / 2, k_highScoreYPosStart );

	for( int i = 0; i < k_savedHighScoresNum; i++ )
	{
		HiScore currentHiScore = m_pHiScoreManager->getHiScoreByIndex( i );
		// Had to use ss because of weird error when putting currentHiScore.getScore() inside .setString param
		std::stringstream().swap( ss );
		ss << currentHiScore.getScore();

		m_pInitialsArray[i].init( font, currentHiScore.getInitials(), k_scoreboardFontSize );
		m_pInitialsArray[i].setPosition( ( k_windowWidth / 2 ) - k_scoreboardXSpacing, k_highScoreYPosStart + k_scoreboardYSpaceFromTitle + ( k_scoreboardYSpacing * i ) );

		m_pScoresArray[i].init( font, ss.str(), k_scoreboardFontSize );
		m_pScoresArray[i].setPosition( k_windowWidth / 2 + k_scoreboardXSpacing, k_highScoreYPosStart + k_scoreboardYSpaceFromTitle + ( k_scoreboardYSpacing * i ) );
	}

	m_pBackText->init( font, k_backString, k_menuElementsSize );
	m_pBackText->setPosition( k_windowWidth / 2, k_windowHeight - k_highScoreYPosStart );
}

void MainMenuManager::initOptionsScreen()
{
	const sf::Font& font = m_pFontManager->getMainFont();

	std::stringstream ss;

	m_pOptionsElementsArray = new GameText[k_optionsElementsNum];

	ss << k_optionsFxVolumeString << m_pSoundManager->getFxVolume();
	m_pOptionsElementsArray[0].init( font, ss.str(), k_menuElementsSize );
	m_pOptionsElementsArray[0].setPosition( k_windowWidth / 2, k_windowWidth / 3 - k_menuElementsYIncrement );

	std::stringstream().swap( ss );

	ss << k_optionsMusicVolumeString << m_pSoundManager->getMusicVolume();
	m_pOptionsElementsArray[1].init( font, ss.str(), k_menuElementsSize );
	m_pOptionsElementsArray[1].setPosition( k_windowWidth / 2, k_windowWidth / 3 );

	m_pOptionsElementsArray[2].init( font, k_backString, k_menuElementsSize );
	m_pOptionsElementsArray[2].setPosition( k_windowWidth / 2, k_windowWidth / 3 + ( k_menuElementsYIncrement * 2 ) );
}

void MainMenuManager::menuUpdate( float deltaTime )
{
	if( m_pInputManager->downIsPressed() && !m_downIsPressed )
	{
		m_pMenuElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_selectedElementNum = ( m_selectedElementNum + 1 ) % k_menuElementsNum;
		m_pMenuMoveSound->play();
	}

	if( m_pInputManager->upIsPressed() && !m_upIsPressed )
	{
		m_pMenuElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_selectedElementNum = ( ( k_menuElementsNum - 1 ) + m_selectedElementNum ) % k_menuElementsNum;
		m_pMenuMoveSound->play();
	}

	m_pSelectedElement = &m_pMenuElementsArray[m_selectedElementNum];


	if( m_pInputManager->enterIsPressed() && !m_enterIsPressed )
	{
		switch( m_selectedElementNum )
		{
			//Start Game
		case 0:
		{
			m_shouldGameStart = true;
		}
		break;
		//Leaderboard
		case 1:
		{
			m_menuState = MenuState::Leaderboard;
			m_pSelectedElement = m_pBackText;
		}
		break;
		//Options
		case 2:
		{
			m_pMenuElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
			m_menuState = MenuState::Options;
			m_selectedElementNum = 0;
			m_pSelectedElement = &m_pOptionsElementsArray[m_selectedElementNum];
		}
		break;
		//Credits
		case 3:
		{
			m_pCredits->reinitPos();
			m_menuState = MenuState::Credits;
		}
		break;
		//Exit
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

	selectedElementAnim( deltaTime );
}

void MainMenuManager::leaderboardUpdate( float deltaTime )
{
	if( m_pInputManager->enterIsPressed() && !m_enterIsPressed )
	{
		m_menuState = MenuState::Main;
		m_selectedElementNum = 0;
		m_pSelectedElement = &m_pMenuElementsArray[m_selectedElementNum];
	}

	m_enterIsPressed = m_pInputManager->enterIsPressed();
	selectedElementAnim( deltaTime );
}

void MainMenuManager::optionsUpdate( float deltaTime )
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
		m_menuState = MenuState::Main;
		m_selectedElementNum = 0;
		m_pMenuDenySound->play();
	}
	if( m_pInputManager->escIsPressed() && !m_escIsPressed )
	{
		m_pOptionsElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_pSoundManager->saveOptionsData();
		m_menuState = MenuState::Main;
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

void MainMenuManager::resetVolume()
{
	m_pMenuMusic->setVolume( m_pSoundManager->getMusicVolume() );
	m_pMenuConfirmSound->setVolume( m_pSoundManager->getFxVolume() );
	m_pMenuDenySound->setVolume( m_pSoundManager->getFxVolume() );
	m_pMenuMoveSound->setVolume( m_pSoundManager->getFxVolume() );
}

void MainMenuManager::resetOptionStrings()
{
	std::stringstream ss;

	ss << k_optionsFxVolumeString << m_pSoundManager->getFxVolume();
	m_pOptionsElementsArray[0].setString( ss.str() );

	std::stringstream().swap( ss );

	ss << k_optionsMusicVolumeString << m_pSoundManager->getMusicVolume();
	m_pOptionsElementsArray[1].setString( ss.str() );
}

void MainMenuManager::selectedElementAnim( float deltaTime )
{
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

	if( m_animScaleIncrease )
	{
		m_animScale += ( m_animScaleSpeed * deltaTime );
	}

	else if( !m_animScaleIncrease )
	{
		m_animScale -= ( m_animScaleSpeed * deltaTime );
	}

	m_pSelectedElement->setScale( m_animScale, m_animScale );
}

bool MainMenuManager::shouldGameStart()
{
	return m_shouldGameStart;
}