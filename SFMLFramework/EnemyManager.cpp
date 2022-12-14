#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "EnemyManager.h"
#include "BulletManager.h"
#include "Enemy.h"
#include "ReferenceManager.h"
#include "TextureManager.h"
#include "WaveManager.h"
#include "Helpers.h"
#include "Settings.h"

EnemyManager::EnemyManager()
	: m_pEnemyArray				( nullptr )
	, m_pWindow					( nullptr )
	, m_pTextureManager			( nullptr )
	, m_pBulletManager			( nullptr )
	, m_pWaveManager			( nullptr )
	, m_formationPos			( 0.0f, 0.0f )
	, m_enemyWidth				( 0.0f )
	, m_yAtMoveStart			( 0.0f )
	, m_totalHorizontalSpace	( 0.0f )
	, m_isMovingLeft			( false )
	, m_isAdvancing				( false )
	, m_canFire					( false )
	, m_enemyCount				( 0 )
	, m_activeEnemies			( 0 )
	, m_inFormationEnemies		( 0 )
	, m_enemiesReadyToFire		( 0 )
	, m_enemiesDiving			( 0 )
	, m_spawnTimer				( 0.0f )
	, m_fireTimer				( 0.0f )
	, m_diveTimer				( 0.0f )
	, m_secondsToNextFire		( 0.0f )
	, m_secondsToNextDive		( 0.0f )
{
}

EnemyManager::~EnemyManager()
{	
	safeDelete( m_pBulletManager );
	safeDeleteArray( m_pEnemyArray );
}

void EnemyManager::update( float deltaTime )
{
	switch( m_pWaveManager->getState() )
	{
		case WaveState::FlyingToFormation:
		{
			activeEnemyCount();

			m_spawnTimer += deltaTime * k_enemySpawnSpeed;
			int elapsedSecondsAsInt = static_cast< int >( m_spawnTimer );

			if( elapsedSecondsAsInt >= m_activeEnemies )
			{
				elapsedSecondsAsInt = m_activeEnemies;
			}

			for( int i = 0; i < elapsedSecondsAsInt; i++ )
			{
				if( m_pEnemyArray[i].getCurrentState() == EnemyState::Retreating )
				{
					m_pEnemyArray[i].update( deltaTime );
				}
			}

			if( m_pEnemyArray[m_activeEnemies - 1].getCurrentState() == EnemyState::InFormation )
			{
				m_pWaveManager->changeState( WaveState::InProgress );
			}
		}
		break;
		case WaveState::InProgress:
		{
			{
				activeEnemyCount();

				attackCheck( deltaTime );

				m_pBulletManager->update( deltaTime );

				move( deltaTime );
			}

			for( int i = 0; i < m_enemyCount; i++ )
			{
				if( m_pEnemyArray[i].getCurrentState() != EnemyState::Inactive )
				{
					m_pEnemyArray[i].update( deltaTime );
				}
			}
		}
		break;
		case WaveState::Defeated:
		{
			m_pBulletManager->update( deltaTime );
		}
		break;
	}
}



void EnemyManager::draw()
{
	m_pBulletManager->draw();
	for( int i = 0; i < m_enemyCount; i++ )
	{
		if( m_pEnemyArray[i].getCurrentState() != EnemyState::Inactive )
		{
			m_pWindow->draw( m_pEnemyArray[i] );
		}
	}
}

void EnemyManager::init( const ReferenceManager& refManager )
{
	m_pWindow = &refManager.getWindowHandle();

	m_pTextureManager = &refManager.getTextureManager();

	m_pWaveManager = &refManager.getWaveManager();

	m_pBulletManager = new BulletManager();

	m_pBulletManager->init( refManager );

	m_pBulletManager->initEnemyBullets();

	initEnemies( refManager );
}

// Initialise enemy values
void EnemyManager::initEnemies( const ReferenceManager& refManager )
{
	// Finding the max enemies needed by iterating through the wave num array
	// The max num is set to m_enemyCount
	for( auto it : k_waveTotalEnemies )
	{
		if( it > m_enemyCount )
		{
			m_enemyCount = it;
		}
	}

	// Creating the enemies
	m_pEnemyArray = new Enemy[m_enemyCount];

	for( int i = 0; i < m_enemyCount; i++ )
	{
		m_pEnemyArray[i].init( refManager, *m_pBulletManager );
	}

	// Getting the width to use for spacing the enemies out
	m_enemyWidth = m_pEnemyArray->getGlobalBounds().width;
}

int EnemyManager::getEnemyCount()
{
	return m_enemyCount;
}

int EnemyManager::getActiveEnemyCount()
{
	return m_activeEnemies;
}

Enemy& EnemyManager::getEnemyByIndex( const int index )
{
	return m_pEnemyArray[index];
}

void EnemyManager::move( float deltaTime )
{
	if( m_isAdvancing )
	{
		m_formationPos.y += k_enemyYSpeed * deltaTime;

		if( m_formationPos.y >= m_yAtMoveStart + k_enemyYMoveDistance )
		{
			m_formationPos.y = m_yAtMoveStart + k_enemyYMoveDistance;
			m_isAdvancing = false;
		}
	}
	else
	{
		if( m_isMovingLeft )
		{
			m_formationPos.x -= k_enemyXSpeed * deltaTime;

			if( m_formationPos.x <= m_enemyWidth / 2 )
			{
				m_formationPos.x = m_enemyWidth / 2;
				m_isMovingLeft = false;
				m_isAdvancing = true;
				m_yAtMoveStart = m_formationPos.y;
			}
		}
		else
		{
			m_formationPos.x += k_enemyXSpeed * deltaTime;

			if( m_formationPos.x >= k_windowWidth - m_totalHorizontalSpace + ( m_enemyWidth / 2 ) )
			{
				m_formationPos.x = k_windowWidth - m_totalHorizontalSpace + ( m_enemyWidth / 2 );
				m_isMovingLeft = true;
				m_isAdvancing = true;
				m_yAtMoveStart = m_formationPos.y;
			}
		}
	}
}

void EnemyManager::attackCheck( float deltaTime )
{
	m_fireTimer += deltaTime;
	m_diveTimer += deltaTime;
	
	bool shouldAttack = true;
	int randomNum = Math::randomiseInt( 0, 1 );

	switch( randomNum )
	{
		// Shoot attack
		case 0:
		{
			// Checking if enemies can fire and if there are active enemies left to fire
			if( m_enemiesReadyToFire < k_enemyMaxReadyToFire && m_inFormationEnemies > 0 && m_fireTimer > m_secondsToNextFire )
			{
				// Randomising which ship to fire
				int shipToFire = Math::randomiseInt( 0, m_enemyCount - 1 );
				int origShipNum = shipToFire;

				// While the randomised shipToFire is not active, increments the shipToFire until an active one is found
				while( m_pEnemyArray[shipToFire].getCurrentState() != EnemyState::InFormation || m_pEnemyArray[shipToFire].isReadyToFire() )
				{
					shipToFire++;

					// If end of the array is reached without finding an active ship, resets to the first element
					if( shipToFire >= m_enemyCount )
					{
						shipToFire = 0;
					}

					// If the num cycles back to the original num, sets a bool to not attack in order to break out from the loop
					if( shipToFire == origShipNum )
					{
						shouldAttack = false;
						break;
					}
				}

				if( shouldAttack )
				{
					// Fires bullet from the chosen ships position
					m_pEnemyArray[shipToFire].setToFire();

					m_secondsToNextFire = Math::randomiseFloat( k_enemyMinFireDelay, k_enemyMaxFireDelay );
					m_fireTimer = 0.0f;
				}
			}
		}
		break;
		// Dive attack
		case 1:
		{
			// Checking if enemies can dive and if there are active enemies left to dive
			if( m_enemiesDiving < k_enemyMaxDiving && m_inFormationEnemies > 0 && m_diveTimer > m_secondsToNextDive )
			{
				// Randomising which ship to dive
				int shipToDive = Math::randomiseInt( 0, m_enemyCount - 1 );
				int origShipNum = shipToDive;

				// While the randomised shipToDive is not active, increments the shipToDive until an active one is found
				while( m_pEnemyArray[shipToDive].getCurrentState() != EnemyState::InFormation || m_pEnemyArray[shipToDive].isReadyToFire() )
				{
					shipToDive++;

					// If end of the array is reached without finding an active ship, resets to the first element
					if( shipToDive >= m_enemyCount )
					{
						shipToDive = 0;
					}

					if( shipToDive == origShipNum )
					{
						shouldAttack = false;
						break;
					}
				}

				if( shouldAttack )
				{
					// Tells ship to dive at the player
					m_pEnemyArray[shipToDive].startDiving();

					m_secondsToNextDive = Math::randomiseFloat( k_enemyMinDiveDelay, k_enemyMaxDiveDelay );
					m_diveTimer = 0.0f;
				}
			}
		}
		break;
	}
}

void EnemyManager::setupWave( int rows, int enemiesPerRow )
{
	// Calculating spawn position based on the space that will be used
	float totalSpaceOfHorizontalGaps = k_gapBetweenEnemies * ( enemiesPerRow - 1 );
	m_totalHorizontalSpace = ( m_enemyWidth * enemiesPerRow ) + totalSpaceOfHorizontalGaps;
	float startPos = ( k_windowWidth - m_totalHorizontalSpace ) / 2;

	m_formationPos = sf::Vector2f( startPos + ( m_enemyWidth / 2 ), k_enemyYStart );

	sf::Vector2f leftSpawn = k_leftSpawn;
	sf::Vector2f rightSpawn = k_rightSpawn;
	leftSpawn.x -= m_enemyWidth;
	rightSpawn.x += m_enemyWidth;


	for( int i = 0; i < rows; i++ )
	{
		for( int j = 0; j < enemiesPerRow; j++ )
		{
			sf::Vector2f positionInFormation = sf::Vector2f( m_formationPos.x + ( ( m_enemyWidth + k_gapBetweenEnemies ) * j ), k_enemyYStart + ( k_enemyRowGap * i ) );

			if( ( enemiesPerRow * i + j ) % 2 )
			{
				m_pEnemyArray[enemiesPerRow * i + j].initPositions( m_formationPos, positionInFormation, leftSpawn );
			}
			else
			{
				m_pEnemyArray[enemiesPerRow * i + j].initPositions( m_formationPos, positionInFormation, rightSpawn );
			}
		}
	}
}

void EnemyManager::beginWave()
{
	m_isMovingLeft = false;
	m_isAdvancing = false;

	m_secondsToNextFire = k_enemyDefaultFireDelay;

	m_secondsToNextDive = k_enemyMaxDiveDelay;

	m_spawnTimer = 0.0f;
	m_diveTimer = 0.0f;
	m_fireTimer = 0.0f;
}

void EnemyManager::activeEnemyCount()
{
	m_activeEnemies = 0;
	m_inFormationEnemies = 0;
	m_enemiesReadyToFire = 0;
	m_enemiesDiving = 0;
	for( int i = 0; i < m_enemyCount; i++ )
	{
		if( m_pEnemyArray[i].getCurrentState() != EnemyState::Inactive )
		{
			m_activeEnemies++;
		}
		if( m_pEnemyArray[i].getCurrentState() == EnemyState::InFormation )
		{
			m_inFormationEnemies++;

			if ( m_pEnemyArray[i].isReadyToFire() )
			{
				m_enemiesReadyToFire++;
			}
		}
		if( m_pEnemyArray[i].getCurrentState() == EnemyState::Attacking )
		{
			m_enemiesDiving++;
		}
	}
}

void EnemyManager::reset()
{
	for( int i = 0; i < m_enemyCount; i++ )
	{
		m_pEnemyArray[i].reset();
	}

	m_activeEnemies = 0;
	m_inFormationEnemies = 0;
	m_enemiesReadyToFire = 0;
	m_enemiesDiving = 0;
	m_canFire = false;
	m_pBulletManager->reset();
}