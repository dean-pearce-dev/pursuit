#include "GameplayDirector.h"
#include "Helpers.h"
#include "BackgroundManager.h"
#include "BarrierManager.h"
#include "CollidableManager.h"
#include "Director.h"
#include "EndGameManager.h"
#include "EnemyManager.h"
#include "GameSound.h"
#include "HiScoreManager.h"
#include "HudManager.h"
#include "PauseManager.h"
#include "ReferenceManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "WaveManager.h"
#include "Player.h"

GameplayDirector::GameplayDirector()
	: m_pBackgroundManager	( nullptr )
	, m_pEnemyManager		( nullptr )
	, m_pBarrierManager		( nullptr )
	, m_pCollidableManager	( nullptr )
	, m_pHudManager			( nullptr )
	, m_pHiScoreManager		( nullptr )
	, m_pEndGameManager		( nullptr )
	, m_pPauseManager		( nullptr )
	, m_pSoundManager		( nullptr )
	, m_pStateManager		( nullptr )
	, m_pWaveManager		( nullptr )
	, m_pPlayer				( nullptr )
	, m_pGameMusic			( nullptr )
	, m_shouldReturnToMenu	( false )
{
}

GameplayDirector::~GameplayDirector()
{
	safeDelete( m_pGameMusic );
	safeDelete( m_pWaveManager );
	safeDelete( m_pEnemyManager );
	safeDelete( m_pBarrierManager );
	safeDelete( m_pCollidableManager );
	safeDelete( m_pEndGameManager );
	safeDelete( m_pPauseManager );
	safeDelete( m_pHudManager );
	safeDelete( m_pPlayer );
}

void GameplayDirector::update( float deltaTime )
{
	switch( m_pStateManager->getInGameState() )
	{
		case InGameState::Game: case InGameState::Pause:
		{
			if( m_pStateManager->getInGameState() != InGameState::Pause )
			{
				m_pBackgroundManager->update( deltaTime );
				m_pEnemyManager->update( deltaTime );
				m_pWaveManager->update( deltaTime );
				m_pBarrierManager->update( deltaTime );
				m_pPlayer->update( deltaTime );
				m_pHudManager->update();

				if( m_pWaveManager->isLevelComplete() )
				{
					if( m_pPlayer->getScore() > m_pHiScoreManager->getLowestScore() )
					{
						m_pEndGameManager->goToEnterScore();
					}
					else
					{
						m_pStateManager->setInGameState( InGameState::GameOver );
					}

					m_pEndGameManager->resetScoreStrings();
				}
				else if( playerIsDefeated() )
				{
					if( m_pPlayer->getScore() > m_pHiScoreManager->getLowestScore() )
					{
						m_pEndGameManager->goToEnterScore();
					}
					else
					{
						m_pStateManager->setInGameState( InGameState::Victory );
					}

					m_pEndGameManager->resetScoreStrings();
				}
			}

			m_pPauseManager->update( deltaTime );
			m_shouldReturnToMenu = m_pPauseManager->shouldReturnToMenu();
		}
		break;
		case InGameState::EnterHiScore: case InGameState::HiScoreBoard: case InGameState::Victory: case InGameState::GameOver:
		{
			m_pBackgroundManager->update( deltaTime );
			m_pEndGameManager->update( deltaTime );
			m_shouldReturnToMenu = m_pEndGameManager->shouldReturnToMenu();
		}
		break;
	}
}

void GameplayDirector::draw()
{


	switch( m_pStateManager->getInGameState() )
	{
		case InGameState::Game: case InGameState::Pause:
		{
			// Drawing the background first
			m_pBackgroundManager->draw();

			// Drawing the enemies
			m_pEnemyManager->draw();

			// Drawing the barriers
			m_pBarrierManager->draw();

			// Drawing the player
			m_pPlayer->draw();

			m_pHudManager->draw();

			if( m_pStateManager->getInGameState() == InGameState::Pause )
			{
				// Drawing the pause menu
				m_pPauseManager->draw();
			}

		}
		break;
		case InGameState::EnterHiScore: case InGameState::HiScoreBoard: case InGameState::Victory: case InGameState::GameOver:
		{
			// Drawing the background first
			m_pBackgroundManager->draw();
			m_pEndGameManager->draw();
		}
		break;
	}
}

void GameplayDirector::init( ReferenceManager& refManager )
{
	m_pStateManager = &refManager.getStateManager();
	m_pBackgroundManager = &refManager.getBackgroundManager();
	m_pHiScoreManager = &refManager.getHiScoreManager();

	// Creating the necessary game objects
	m_pEnemyManager = new EnemyManager();
	m_pBarrierManager = new BarrierManager();
	m_pCollidableManager = new CollidableManager();
	m_pHudManager = new HudManager();
	m_pEndGameManager = new EndGameManager();
	m_pPauseManager = new PauseManager();
	m_pWaveManager = new WaveManager();
	m_pPlayer = new Player();
	m_pGameMusic = new GameSound();

	// Ref Manager needs to init gameplay refs here
	refManager.initGameplayRefs( *this );

	// Initializing the objects
	m_pGameMusic->setBuffer( refManager.getSoundManager().getGameMusic() );
	m_pGameMusic->setVolume( refManager.getSoundManager().getMusicVolume() );
	m_pBackgroundManager->reset();
	m_pEnemyManager->init( refManager );
	m_pBarrierManager->init( refManager );
	m_pPlayer->init( refManager );
	m_pHiScoreManager->init();
	m_pHudManager->init( refManager );
	m_pEndGameManager->init( refManager );
	m_pPauseManager->init( refManager );
	m_pWaveManager->init( refManager );

	// Initializing and giving the collidable manager what it needs to track collidable objects
	m_pCollidableManager->init( *m_pPlayer, *m_pEnemyManager, *m_pBarrierManager );

	m_pGameMusic->setLoop( true );
	m_pGameMusic->play();
}

void GameplayDirector::playMusic()
{
	m_pGameMusic->play();
}

void GameplayDirector::pauseMusic()
{
	m_pGameMusic->pause();

}

bool GameplayDirector::shouldReturnToMenu()
{
	return m_shouldReturnToMenu;
}

bool GameplayDirector::playerIsDefeated()
{
	return m_pPlayer->getState() == PlayerState::Inactive;
}

void GameplayDirector::resetGame()
{
	m_pWaveManager->reset();
	m_pEnemyManager->reset();
	m_pBarrierManager->reset();
	m_pPlayer->reset();
	m_pGameMusic->stop();
	m_pGameMusic->play();
}

BackgroundManager& GameplayDirector::getBackgroundManager()
{
	return *m_pBackgroundManager;
}

BarrierManager& GameplayDirector::getBarrierManager()
{
	return *m_pBarrierManager;
}

CollidableManager& GameplayDirector::getCollidableManager()
{
	return *m_pCollidableManager;
}

EnemyManager& GameplayDirector::getEnemyManager()
{
	return *m_pEnemyManager;
}

PauseManager& GameplayDirector::getPauseManager()
{
	return *m_pPauseManager;
}

Player& GameplayDirector::getPlayer()
{
	return *m_pPlayer;
}

SoundManager& GameplayDirector::getSoundManager()
{
	return *m_pSoundManager;
}

StateManager& GameplayDirector::getStateManager()
{
	return *m_pStateManager;
}

WaveManager& GameplayDirector::getWaveManager()
{
	return *m_pWaveManager;
}