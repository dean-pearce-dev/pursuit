#include "BulletManager.h"
#include "EnemyBullet.h"
#include "PlayerBullet.h"
#include "Helpers.h"
#include "ReferenceManager.h"
#include "TextureManager.h"
#include "Settings.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

BulletManager::BulletManager()
	: m_pWindow				( nullptr )
	, m_pCollidableManager	( nullptr )
	, m_pTextureManager		( nullptr )
	, m_pooledBulletCount	( 0 )
	, m_firedBullets		( 0 )
	, m_maxFiredBullets		( 0 )
	, m_reloadTimer			( 0.0f )
	, m_reloadDelay			( 0.0f )
{
}

BulletManager::~BulletManager()
{
	// Using for loop to delete each pointer within the vector
	for( int i = 0; i < m_pooledBulletCount; i++ )
	{
		safeDelete( m_pBulletArray[i] );
	}
}

void BulletManager::update( float deltaTime )
{
	for( int i = 0; i < m_pooledBulletCount; i++ )
	{
		if( m_pBulletArray[i]->isActive() )
		{
			m_pBulletArray[i]->update( deltaTime );
		}
	}

	// Reload bullets if any are fired
	if( m_firedBullets > 0 )
	{
		reloadBullets( deltaTime );
	}
}

void BulletManager::draw()
{
	for( int i = 0; i < m_pooledBulletCount; i++ )
	{
		if( m_pBulletArray[i]->isActive() )
		{
			// Drawing each bullet by the pointer to it as it is derived from game sprite
			m_pWindow->draw( *m_pBulletArray[i] );
		}
	}
}

void BulletManager::init( const ReferenceManager& refManager )
{
	m_pWindow = &refManager.getWindowHandle();
	m_pCollidableManager = &refManager.getCollidableManager();
	m_pTextureManager = &refManager.getTextureManager();
}

// Function for initiating the vector pool of player bullets
void BulletManager::initPlayerBullets()
{
	m_reloadDelay = k_playerReloadDelay;
	m_maxFiredBullets = k_playerMaxFiredBullets;

	for( int i = 0; i < k_playerBulletArraySize; i++ )
	{
		// Assigning a new PlayerBullet to a temp variable to use it's specific function (setEnemyManager)
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->setCollidableManager( *m_pCollidableManager );
		newBullet->init( m_pTextureManager->getPlayerBullet() );

		// Passing the pointer into the vector
		m_pBulletArray.push_back( newBullet );

		// Incrementing pool count
		m_pooledBulletCount++;
	}
}

void BulletManager::initEnemyBullets()
{
	m_reloadDelay = k_enemyReloadDelay;
	m_maxFiredBullets = k_enemyMaxFiredBullets;

	for( int i = 0; i < k_enemyBulletArraySize; i++ )
	{
		// Assigning a new EnemyBullet to a temp variable to use it's specific function (setPlayerRef)
		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->setCollidableManager( *m_pCollidableManager );
		newBullet->init( m_pTextureManager->getEnemyBullet() );

		// Passing the pointer into the vector
		m_pBulletArray.push_back( newBullet );

		// Incrementing pool count
		m_pooledBulletCount++;
	}
}

// Firing a bullet
void BulletManager::fire( const sf::Vector2f& currentPos, BulletDir bulletDir )
{
	for( int i = 0; i < m_pooledBulletCount; i++ )
	{
		// Checking if the bullet is active/inactive to determine whether it can be fired
		if( !m_pBulletArray[i]->isActive() )
		{
			m_pBulletArray[i]->setPosition( currentPos );
			m_pBulletArray[i]->setDir( bulletDir );
			switch( bulletDir )
			{
				case BulletDir::Up: case BulletDir::Down:
				{
					m_pBulletArray[i]->setRotation( 0.0f );
				}
				break;
				case BulletDir::UpLeft:
				{
					m_pBulletArray[i]->setRotation( -k_diagonalShotAngle );
				}
				break;
				case BulletDir::UpRight:
				{
					m_pBulletArray[i]->setRotation( k_diagonalShotAngle );
				}
				break;
			}
			m_pBulletArray[i]->setActive( true );
			m_firedBullets++;
			return;
		}
	}
}

void BulletManager::reloadBullets( float deltaTime )
{
	m_reloadTimer += deltaTime;

	if( m_reloadTimer > m_reloadDelay && m_firedBullets > 0 )
	{
		m_firedBullets--;
		m_reloadTimer = 0.0f;
	}
}

const int BulletManager::getFiredBullets()
{
	return m_firedBullets;
}

bool BulletManager::canFire()
{
	return m_firedBullets < m_maxFiredBullets;
}

void BulletManager::reset()
{
	m_firedBullets = 0;
	m_reloadTimer = 0.0f;

	for( int i = 0; i < m_pooledBulletCount; i++ )
	{
		m_pBulletArray[i]->disable();
	}
}