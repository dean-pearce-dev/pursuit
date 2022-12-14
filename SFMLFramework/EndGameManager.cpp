#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>
#include <iostream>

#include "EndGameManager.h"
#include "FontManager.h"
#include "GameplayDirector.h"
#include "GameSound.h"
#include "GameText.h"
#include "Helpers.h"
#include "HiScore.h"
#include "HiScoreManager.h"
#include "InputManager.h"
#include "Player.h"
#include "ReferenceManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "Settings.h"

EndGameManager::EndGameManager()
	: m_pWindow				( nullptr )
	, m_pEndElementsArray	( nullptr )
	, m_pFontManager		( nullptr )
	, m_pInputManager		( nullptr )
	, m_pStateManager		( nullptr )
	, m_pGameplayDirector	( nullptr )
	, m_pHiScoreManager		( nullptr )
	, m_pPlayer				( nullptr )
	, m_pSelectedElement	( nullptr )
	, m_pMenuMoveSound		( nullptr )
	, m_pMenuConfirmSound	( nullptr )
	, m_pMenuDenySound		( nullptr )
	, m_pYouScoredText		( nullptr )
	, m_pGameOverText		( nullptr )
	, m_pVictoryText		( nullptr )
	, m_pHighScoresText		( nullptr )
	, m_pEnterInitialsText	( nullptr )
	, m_pNewHiScoreText		( nullptr )
	, m_pInitialsScoreText	( nullptr )
	, m_pContinueText		( nullptr )
	, m_pInitialsArray		( nullptr )
	, m_pScoresArray		( nullptr )
	, m_pInitialsInputArray	( nullptr )
	, m_selectedElementNum	( 0 )
	, m_animScale			( k_animDefaultScale )
	, m_animScaleDefault	( k_animDefaultScale )
	, m_animScaleSpeed		( k_animScaleSpeed )
	, m_animScaleOffset		( k_animScaleOffset )
	, m_animScaleIncrease	( false )
	, m_upIsPressed			( false )
	, m_downIsPressed		( false )
	, m_leftIsPressed		( false )
	, m_rightIsPressed		( false )
	, m_escIsPressed		( false )
	, m_enterIsPressed		( true )
	, m_shouldReturnToMenu	( false )
{

}

EndGameManager::~EndGameManager()
{
	safeDeleteArray( m_pEndElementsArray );
	safeDeleteArray( m_pInitialsArray );
	safeDeleteArray( m_pScoresArray );
	safeDeleteArray( m_pInitialsInputArray );
	safeDelete( m_pMenuMoveSound );
	safeDelete( m_pMenuConfirmSound );
	safeDelete( m_pMenuDenySound );
	safeDelete( m_pYouScoredText );
	safeDelete( m_pGameOverText );
	safeDelete( m_pVictoryText );
	safeDelete( m_pHighScoresText );
	safeDelete( m_pContinueText );
	safeDelete( m_pNewHiScoreText );
	safeDelete( m_pEnterInitialsText );
	safeDelete( m_pInitialsScoreText );
}

void EndGameManager::update( float deltaTime )
{
	switch( m_pStateManager->getInGameState() )
	{
		case InGameState::EnterHiScore: case InGameState::HiScoreBoard:
		{
			hiScoreScreen( deltaTime );
		}
		break;
		case InGameState::GameOver: case InGameState::Victory:
		{
			endScreen( deltaTime );
		}
		break;
	}
}

void EndGameManager::draw()
{
	switch( m_pStateManager->getInGameState() )
	{
		// Enter initials
		case InGameState::EnterHiScore:
		{
			m_pWindow->draw( *m_pNewHiScoreText );
			m_pWindow->draw( *m_pInitialsScoreText );
			m_pWindow->draw( *m_pEnterInitialsText );

			for( int i = 0; i < k_scoreInitialsLength; i++ )
			{
				m_pWindow->draw( m_pInitialsInputArray[i] );
			}
		}
		break;
		// Scoreboard
		case InGameState::HiScoreBoard:
		{
			m_pWindow->draw( *m_pHighScoresText );
			m_pWindow->draw( *m_pContinueText );

			for( int i = 0; i < k_savedHighScoresNum; i++ )
			{
				m_pWindow->draw( m_pInitialsArray[i] );
				m_pWindow->draw( m_pScoresArray[i] );
			}

		}
		break;
		// Defeated
		case InGameState::GameOver:
		{
			m_pWindow->draw( *m_pGameOverText );
			m_pWindow->draw( *m_pYouScoredText );

			drawElementsArray();
		}
		break;
		// Victory
		case InGameState::Victory:
		{
			m_pWindow->draw( *m_pVictoryText );
			m_pWindow->draw( *m_pYouScoredText );

			drawElementsArray();
		}
		break;
	}
}

void EndGameManager::init( const ReferenceManager& refManager )
{
	// Getting references to the window and the font manager
	m_pWindow = &refManager.getWindowHandle();
	m_pFontManager = &refManager.getFontManager();
	m_pInputManager = &refManager.getInputManager();
	m_pStateManager = &refManager.getStateManager();
	m_pGameplayDirector = &refManager.getGameplayDirector();
	m_pPlayer = &refManager.getPlayer();

	m_pHiScoreManager = &refManager.getHiScoreManager();
	m_pHiScoreManager->init();

	// Creating the sounds
	m_pMenuMoveSound = new GameSound();
	m_pMenuConfirmSound = new GameSound();
	m_pMenuDenySound = new GameSound();

	// Setting the sounds
	m_pMenuMoveSound->setBuffer( refManager.getSoundManager().getMenuMove() );
	m_pMenuConfirmSound->setBuffer( refManager.getSoundManager().getMenuConfirm() );
	m_pMenuDenySound->setBuffer( refManager.getSoundManager().getMenuDeny() );

	// Setting the volume
	m_pMenuMoveSound->setVolume( refManager.getSoundManager().getFxVolume() );
	m_pMenuConfirmSound->setVolume( refManager.getSoundManager().getFxVolume() );
	m_pMenuDenySound->setVolume( refManager.getSoundManager().getFxVolume() );

	setupEndScreen( refManager );
	setupScoreScreen( refManager );
	setupHiScoreInputScreen( refManager );

	// Setting the selected menu element based on int
	m_pSelectedElement = &m_pEndElementsArray[m_selectedElementNum];
}

void EndGameManager::hiScoreScreen( float deltaTime )
{
	switch( m_pStateManager->getInGameState() )
	{
		case InGameState::EnterHiScore:
		{
			//Move initial left
			if( m_pInputManager->leftIsPressed() && !m_leftIsPressed )
			{
				m_pInitialsInputArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
				m_selectedElementNum = ( ( k_scoreInitialsLength - 1 ) + m_selectedElementNum ) % k_scoreInitialsLength;
				m_pMenuMoveSound->play();
			}
			//Move initial right
			if( m_pInputManager->rightIsPressed() && !m_rightIsPressed )
			{
				m_pInitialsInputArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
				m_selectedElementNum = ( m_selectedElementNum + 1 ) % k_scoreInitialsLength;
				m_pMenuMoveSound->play();
			}
			// Change initial down
			if( m_pInputManager->downIsPressed() && !m_downIsPressed )
			{
				int alphabetNum = 0;
				std::string letter = m_pInitialsInputArray[m_selectedElementNum].getString();
				alphabetNum = ( letter[0] & 31 ) - 1;
				alphabetNum = ( alphabetNum + 1 ) % 26;

				m_pInitialsInputArray[m_selectedElementNum].setString( k_alphabetUpper[alphabetNum] );

				m_pMenuMoveSound->play();
			}
			// Change initial up
			if( m_pInputManager->upIsPressed() && !m_upIsPressed )
			{
				int alphabetNum = 0;
				std::string letter = m_pInitialsInputArray[m_selectedElementNum].getString();
				alphabetNum = ( letter[0] & 31 ) - 1;
				alphabetNum = ( ( 26 - 1 ) + alphabetNum ) % 26;

				m_pInitialsInputArray[m_selectedElementNum].setString( k_alphabetUpper[alphabetNum] );

				m_pMenuMoveSound->play();
			}

			// Updating selected element
			m_pSelectedElement = &m_pInitialsInputArray[m_selectedElementNum];

			// Enter
			if( m_pInputManager->enterIsPressed() )
			{
				std::string initials;
				initials.resize( k_scoreInitialsLength );

				for( int i = 0; i < k_scoreInitialsLength; i++ )
				{
					initials[i] = m_pInitialsInputArray[i].getString()[0];
				}

				m_pHiScoreManager->addNewHiScore( initials, m_pPlayer->getScore() );
				getNewScores();

				m_selectedElementNum = 0;
				m_pSelectedElement = m_pContinueText;

				// Moving to next state
				m_pStateManager->setInGameState( InGameState::HiScoreBoard );

				m_pMenuConfirmSound->play();
			}

			m_leftIsPressed = m_pInputManager->leftIsPressed();
			m_rightIsPressed = m_pInputManager->rightIsPressed();
			m_downIsPressed = m_pInputManager->downIsPressed();
			m_upIsPressed = m_pInputManager->upIsPressed();

			selectedElementAnim( deltaTime );
		}
		break;
		case InGameState::HiScoreBoard:
		{
			if( m_pInputManager->spaceIsPressed() )
			{
				if( m_pPlayer->getLives() )
				{
					m_pStateManager->setInGameState( InGameState::Victory );
				}
				else
				{
					m_pStateManager->setInGameState( InGameState::GameOver );
				}

				m_pMenuConfirmSound->play();
			}

			selectedElementAnim( deltaTime );
		}
		break;
	}
}

void EndGameManager::endScreen( float deltaTime )
{
	// Menu element down
	if( m_pInputManager->downIsPressed() && !m_downIsPressed )
	{
		m_pEndElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_selectedElementNum = ( m_selectedElementNum + 1 ) % k_endGameElementsNum;
		m_pMenuMoveSound->play();
	}
	// Menu element up
	if( m_pInputManager->upIsPressed() && !m_upIsPressed )
	{
		m_pEndElementsArray[m_selectedElementNum].setScale( m_animScaleDefault, m_animScaleDefault );
		m_selectedElementNum = ( ( k_endGameElementsNum - 1 ) + m_selectedElementNum ) % k_endGameElementsNum;
		m_pMenuMoveSound->play();
	}

	// Enter
	if( m_pInputManager->enterIsPressed() && !m_enterIsPressed )
	{
		switch( m_selectedElementNum )
		{
		//Play Again
		case 0:
		{
			m_pGameplayDirector->resetGame();
			m_pStateManager->setInGameState( InGameState::Game );
		}
		break;
		//Return to Menu
		case 1:
		{
			m_shouldReturnToMenu = true;
		}
		break;
		//Exit
		case 2:
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

	m_pSelectedElement = &m_pEndElementsArray[m_selectedElementNum];

	selectedElementAnim( deltaTime );
}

void EndGameManager::drawElementsArray()
{
	for( int i = 0; i < k_endGameElementsNum; i++ )
	{
		m_pWindow->draw( m_pEndElementsArray[i] );
	}
}

void EndGameManager::selectedElementAnim( float deltaTime )
{
	// Animating the selected element by changing the scale
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
		m_animScaleIncrease = true;
	}

	else if( m_animScale > m_animScaleDefault + m_animScaleOffset )
	{
		m_animScaleIncrease = false;
	}
	m_pSelectedElement->setScale( m_animScale, m_animScale );
}

void EndGameManager::setupEndScreen( const ReferenceManager& refManager )
{
	m_pYouScoredText = new GameText;
	m_pGameOverText = new GameText;
	m_pVictoryText = new GameText;

	const sf::Font& font = refManager.getFontManager().getMainFont();

	std::stringstream ss;
	ss << k_endGameYouScoredString << m_pPlayer->getScore();

	m_pYouScoredText->init( font, ss.str(), k_youScoredStringSize );
	m_pYouScoredText->setPosition( k_windowWidth / 2, k_endGameElementsYStart - k_endGameMenuGap );

	m_pGameOverText->init( font, k_endGameFailString, k_victoryFailStringSize );
	m_pGameOverText->setPosition( k_windowWidth / 2, k_endGameElementsYStart - ( k_endGameMenuGap + k_endGameElementsYIncrement ) );

	m_pVictoryText->init( font, k_endGameVictoryString, k_victoryFailStringSize );
	m_pVictoryText->setPosition( k_windowWidth / 2, k_endGameElementsYStart - ( k_endGameMenuGap + k_endGameElementsYIncrement ) );

	// Setting up the array for the menu elements
	m_pEndElementsArray = new GameText[k_endGameElementsNum];

	for( int i = 0; i < k_endGameElementsNum; i++ )
	{
		m_pEndElementsArray[i].init( font, k_endGameElements[i], k_endElementsSize );
		m_pEndElementsArray[i].setPosition( k_windowWidth / 2, k_endGameElementsYStart + ( k_endGameElementsYIncrement * i ) );
	}
}

void EndGameManager::setupScoreScreen( const ReferenceManager& refManager )
{
	m_pInitialsArray = new GameText[k_savedHighScoresNum];
	m_pScoresArray = new GameText[k_savedHighScoresNum];
	m_pHighScoresText = new GameText;
	m_pContinueText = new GameText;

	std::stringstream ss;

	const sf::Font& font = refManager.getFontManager().getMainFont();

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

	m_pContinueText->init( font, k_continueString, k_continueStringSize );
	m_pContinueText->setPosition( k_windowWidth / 2, k_windowHeight - k_highScoreYPosStart );
}

void EndGameManager::setupHiScoreInputScreen( const ReferenceManager& refManager )
{
	m_pInitialsInputArray = new GameText[ k_scoreInitialsLength ];
	m_pEnterInitialsText = new GameText;
	m_pNewHiScoreText = new GameText;
	m_pInitialsScoreText = new GameText;

	const sf::Font& font = refManager.getFontManager().getMainFont();

	m_pEnterInitialsText->init( font, k_enterInitialsString, k_enterInitialsStringSize );
	m_pEnterInitialsText->setPosition( k_windowWidth / 2, k_enterInitialsYPos );

	m_pNewHiScoreText->init( font, k_newHiScoreString, k_newHiScoreStringSize );
	m_pNewHiScoreText->setPosition( k_windowWidth / 2, k_newHiScoreYPos );

	m_pInitialsScoreText->init( font, k_defaultScoreString, k_initialsScreenScoreSize);
	m_pInitialsScoreText->setPosition( k_windowWidth / 2, k_initialsScreenScoreYPos );

	// Positioning the initials
	for( int i = 0; i < k_scoreInitialsLength; i++ )
	{
		m_pInitialsInputArray[i].init( font, k_defaultInitials[0], k_initialsInputSize, false );

		sf::FloatRect stringRect = m_pInitialsInputArray[i].getLocalBounds();

		float xSpaceUsed = stringRect.width * ( k_scoreInitialsLength - 1 ) + ( k_initialsInputGap * 2 );

		float xPos = ( ( k_windowWidth / 2 ) - ( xSpaceUsed / 2 ) ) + ( stringRect.width + k_initialsInputGap * i);

		m_pInitialsInputArray[i].setPosition( xPos, k_enterInitialsYPos + stringRect.height );
	}
}

void EndGameManager::getNewScores()
{
	for( int i = 0; i < k_savedHighScoresNum; i++ )
	{
		HiScore currentHiScore = m_pHiScoreManager->getHiScoreByIndex( i );
		std::stringstream ss;
		std::stringstream().swap( ss );
		ss << currentHiScore.getScore();


		m_pInitialsArray[i].setString( currentHiScore.getInitials() );
		sf::FloatRect stringRect = m_pInitialsArray[i].getLocalBounds();
		m_pInitialsArray[i].setOrigin( stringRect.left + stringRect.width / 2.0f, stringRect.top + stringRect.height / 2.0f );
		m_pInitialsArray[i].setPosition( ( k_windowWidth / 2 ) - k_scoreboardXSpacing, k_highScoreYPosStart + k_scoreboardYSpaceFromTitle + ( k_scoreboardYSpacing * i ) );

		m_pScoresArray[i].setString( ss.str() );
		stringRect = m_pScoresArray[i].getLocalBounds();
		m_pScoresArray[i].setOrigin( stringRect.left + stringRect.width / 2.0f, stringRect.top + stringRect.height / 2.0f );
		m_pScoresArray[i].setPosition( k_windowWidth / 2 + k_scoreboardXSpacing, k_highScoreYPosStart + k_scoreboardYSpaceFromTitle + ( k_scoreboardYSpacing * i ) );
	}
}

void EndGameManager::goToEnterScore()
{
	m_pStateManager->setInGameState( InGameState::EnterHiScore );
	m_selectedElementNum = 0;
}

bool EndGameManager::shouldReturnToMenu()
{
	return m_shouldReturnToMenu;
}

void EndGameManager::resetScoreStrings()
{
	std::stringstream ss;

	ss << k_endGameYouScoredString << m_pPlayer->getScore();
	m_pYouScoredText->setString( ss.str() );

	sf::FloatRect stringRect = m_pYouScoredText->getLocalBounds();
	m_pYouScoredText->setOrigin( stringRect.left + stringRect.width / 2.0f, stringRect.top + stringRect.height / 2.0f );

	std::stringstream().swap( ss );
	ss << m_pPlayer->getScore();

	m_pInitialsScoreText->setString( ss.str() );
	stringRect = m_pInitialsScoreText->getLocalBounds();
	m_pInitialsScoreText->setOrigin( stringRect.left + stringRect.width / 2.0f, stringRect.top + stringRect.height / 2.0f );
}