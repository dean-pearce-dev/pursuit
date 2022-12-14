#include "WaveManager.h"
#include "Director.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "GameplayDirector.h"
#include "Player.h"
#include "ReferenceManager.h"
#include "Settings.h"

WaveManager::WaveManager()
	: m_pEnemyManager	( nullptr  )
	, m_pPlayer			( nullptr )
	, m_waveTimer		( 0.0f )
	, m_currentWave		( 0 )
	, m_currentState	( WaveState::Awaiting )
{

}

WaveManager::~WaveManager()
{

}

void WaveManager::update( float deltaTime )
{
	switch( m_currentState )
	{
		case WaveState::Awaiting:
		{
			if( m_waveTimer > k_waveStartDelay && m_currentWave < k_totalWaves && !m_pEnemyManager->getActiveEnemyCount() )
			{
				spawnWave();
				changeState( WaveState::FlyingToFormation );
			}

			m_waveTimer += deltaTime;
		}
		break;
		case WaveState::FlyingToFormation:
		{

		}
		break;
		case WaveState::InProgress:
		{
			if( !m_pEnemyManager->getActiveEnemyCount() )
			{
				changeState( WaveState::Defeated );
			}
		}
		break;
		case WaveState::Defeated:
		{
			if( m_waveTimer > k_waveStartDelay && m_currentWave < k_totalWaves && !m_pEnemyManager->getActiveEnemyCount() )
			{
				spawnWave();
				changeState( WaveState::FlyingToFormation );
			}

			m_waveTimer += deltaTime;
		}
		break;
	}
}

void WaveManager::init( const ReferenceManager& refManager )
{
	m_pEnemyManager = &refManager.getEnemyManager();
	m_pPlayer = &refManager.getPlayer();
}

void WaveManager::spawnWave()
{
	m_pEnemyManager->setupWave( k_totalEnemyRows, k_waveTotalEnemies[m_currentWave] / k_totalEnemyRows );
	m_waveTimer = 0.0f;
	m_currentWave++;
}

void WaveManager::initState( WaveState stateToInit )
{
	switch( stateToInit )
	{
		case WaveState::Awaiting:
		{

		}
		break;
		case WaveState::FlyingToFormation:
		{

		}
		break;
		case WaveState::InProgress:
		{
			m_pEnemyManager->beginWave();
			m_currentState = WaveState::InProgress;
			m_pPlayer->setState( PlayerState::Playing );
		}
		break;
		case WaveState::Defeated:
		{

		}
		break;
	}
}

void WaveManager::uninitState()
{
	switch( m_currentState )
	{
	case WaveState::Awaiting:
	{

	}
	break;
	case WaveState::FlyingToFormation:
	{

	}
	break;
	case WaveState::InProgress:
	{

	}
	break;
	case WaveState::Defeated:
	{

	}
	break;
	}
}

void WaveManager::changeState( const WaveState stateToChange )
{
	uninitState();
	initState( stateToChange );
	m_currentState = stateToChange;
}

WaveState WaveManager::getState()
{
	return m_currentState;
}

void WaveManager::setState( WaveState stateToSet )
{
	m_currentState = stateToSet;
}

bool WaveManager::isWaveActive()
{
	return m_pEnemyManager->getActiveEnemyCount();
}

bool WaveManager::isLevelComplete()
{
	return m_currentState == WaveState::Defeated && m_currentWave >= k_totalWaves;
}

void WaveManager::reset()
{
	m_waveTimer = 0.0f;
	m_currentWave = 0;
	m_currentState = WaveState::Awaiting;
}