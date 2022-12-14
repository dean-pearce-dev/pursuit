#include "Enemy.h"
#include "BarrierManager.h"
#include "Barrier.h"
#include "BarrierSegment.h"
#include "BulletManager.h"
#include "CollidableManager.h"
#include "Director.h"
#include "GameSound.h"
#include "Player.h"
#include "ReferenceManager.h"
#include "Settings.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Helpers.h"

Enemy::Enemy()
	: m_pBulletManager				( nullptr )
	, m_pCollidableManager			( nullptr )
	, m_pFormationPos				( nullptr )
	, m_pFireSound					( nullptr )
	, m_pExplosionSound				( nullptr )
	, m_positionInFormation			( 0.0f, 0.0f )
	, m_lerpStartPos				( 0.0f, 0.0f )
	, m_offsetFromFormationOrigin	( 0.0f, 0.0f )
	, m_currentState				( EnemyState::Inactive )
	, m_lerpYValue					( 0.0f )
	, m_lerpXValue					( 0.0f )
	, m_lerpXOffset					( 0.0f )
	, m_lerpedXPos					( 0.0f )
	, m_playerToLerpStartX			( 0.0f )
	, m_fireTimer					( 0.0f )
	, m_scoreValue					( k_enemyScoreValue )
	, m_diveSegmentCount			( 0 )
	, m_fireIsReady					( false )
	, m_waveLeft					( false )
	, m_abovePlayer					( false )
	, m_formationFirstLerp			( false )
{
}

Enemy::~Enemy()
{
	// Safe deleting pointers
	safeDelete( m_pFireSound );
	safeDelete( m_pExplosionSound );
}

void Enemy::update( float deltaTime )
{
	// Getting formation pos from pointer with the offset from that pos
	m_positionInFormation = *m_pFormationPos + m_offsetFromFormationOrigin;

	switch( m_currentState )
	{
		case EnemyState::InFormation:
		{
			setPosition( m_positionInFormation );
			
			// If fire is ready
			if( m_fireIsReady )
			{
				// Checks whether in range of the player
				if ( fireRangeCheck() )
				{ 
					fire();
				}
				else
				{
					// Adding on to the fire timer
					m_fireTimer += deltaTime;

					// If it's been longer than the auto fire delay, then just fires
					if ( m_fireTimer > k_enemyDelayBeforeAutoFire )
					{
						fire();
					}
				}
			}
		}
		break;
		case EnemyState::Attacking:
		{
			// EnemyState::Attacking is the dive bomb state
			diveBomb( deltaTime );
			collisionCheck();
		}
		break;
		case EnemyState::Retreating:
		{
			// Returning to it's position in the formation
			flyToFormation( deltaTime );
			collisionCheck();
		}
		break;
	}
}

void Enemy::init( const ReferenceManager& refManager, BulletManager& bulletManager )
{
	m_pBulletManager = &bulletManager;
	m_pCollidableManager = &refManager.getCollidableManager();

	// Sounds the enemy uses
	m_pFireSound = new GameSound();
	m_pExplosionSound = new GameSound();

	// Setting sound and volume for the sounds
	m_pFireSound->setBuffer( refManager.getSoundManager().getFire() );
	m_pFireSound->setVolume( refManager.getSoundManager().getFxVolume() );
	m_pExplosionSound->setBuffer( refManager.getSoundManager().getExplosion() );
	m_pExplosionSound->setVolume( refManager.getSoundManager().getFxVolume() );

	// Setting the enemy texture and scale
	setCurrentTexture( refManager.getTextureManager().getEnemyShip() );
	setScale( k_defaultEnemyScale, k_defaultEnemyScale );

	// Getting dimensions to use bounds correctly
	setTextureDimensions( getGlobalBounds().width, getGlobalBounds().height );
}

void Enemy::initPositions( const sf::Vector2f& formationPosRef, const sf::Vector2f& positionInFormation, const sf::Vector2f& positionToSpawn )
{
	// Setting initial position
	setPosition( positionToSpawn );

	// Setting formation position
	m_pFormationPos = &formationPosRef;
	m_offsetFromFormationOrigin = positionInFormation - formationPosRef;
	setRotation( 0.0f );

	beginReturning();
}

void Enemy::flyToFormation( float deltaTime )
{ 
	// Point to start formation loop
	sf::Vector2f secondPoint;

	// Comparing x positions to determine whether to fly to the left or right
	if( m_positionInFormation.x >= getPosition().x )
	{
		secondPoint = sf::Vector2f( m_positionInFormation.x - k_formationXOffset, m_positionInFormation.y + k_formationYOffset );
	}
	else
	{
		secondPoint = sf::Vector2f( m_positionInFormation.x + k_formationXOffset, m_positionInFormation.y + k_formationYOffset );
	}
	// Next two points in formation loop
	sf::Vector2f thirdPoint = sf::Vector2f( secondPoint.x, m_positionInFormation.y - k_formationYOffset );
	sf::Vector2f fourthPoint = sf::Vector2f( m_positionInFormation.x, m_positionInFormation.y - k_formationYOffset );

	// Pos for using quadraticLerp between enemy pos and start of formation loop
	sf::Vector2f startPosOffset = sf::Vector2f( secondPoint.x, m_lerpStartPos.y );

	if( !m_formationFirstLerp )
	{

		if( m_lerpYValue < 1.0f )
		{
			// Flying to the start of the loop
			setPosition( Math::quadraticLerp( m_lerpStartPos, startPosOffset, secondPoint, m_lerpYValue ) );
			m_lerpYValue += k_formationReturnSpeed * deltaTime;

			// Using a lookTarget slightly ahead on interpolation, then rotating enemy to look at it
			sf::Vector2f lookTarget = Math::quadraticLerp( m_lerpStartPos, startPosOffset, secondPoint, m_lerpYValue + k_enemyInterpolateOffset );
			float rotation = Math::angleToTarget( getPosition(), lookTarget );
			setRotation( rotation );
		}
		else if( m_lerpYValue >= 1.0f )
		{
			// Resetting values, moving to the next part of the lerp
			m_lerpStartPos = getPosition();
			m_lerpYValue = 0.0f;
			m_formationFirstLerp = true;
		}
	}
	else
	{
		if( m_lerpYValue < 1.0f )
		{
			// Following the pos values set in the first if, using a cubicLerp to loop around to the formation pos with an easeOut
			setPosition( Math::cubicLerp( m_lerpStartPos, thirdPoint, fourthPoint, m_positionInFormation, Math::easeOut( m_lerpYValue ) ) );
			m_lerpYValue += k_formationReturnSpeed * deltaTime;

			// lookTarget with the same logic as above
			sf::Vector2f lookTarget = Math::cubicLerp( m_lerpStartPos, thirdPoint, fourthPoint, m_positionInFormation, Math::easeOut( m_lerpYValue + k_enemyInterpolateOffset ) );
			float rotation = Math::angleToTarget( getPosition(), lookTarget );
			setRotation( rotation );
		}
		else if( m_lerpYValue >= 1.0f )
		{
			// Resetting values, setting enemy to InFormation, and exiting the lerp
			setPosition( m_positionInFormation );
			setCurrentState( EnemyState::InFormation );
			m_lerpYValue = 0.0f;
			setRotation( 0.0f );
			m_formationFirstLerp = false;
		}
	}
}

void Enemy::beginReturning()
{
	// Setting values needed for flyToFormation()
	m_currentState = EnemyState::Retreating;
	m_lerpStartPos = getPosition();
	m_lerpYValue = 0.0f;
	m_lerpXValue = 0.0f;
	m_lerpXOffset = 0.0f;
}

sf::Vector2f Enemy::getFormationPos()
{
	return m_positionInFormation;
}

EnemyState Enemy::getCurrentState()
{
	return m_currentState;
}

void Enemy::setCurrentState( EnemyState stateToSet )
{
	m_currentState = stateToSet;
}

void Enemy::fire()
{
	// Firing a bullet down since enemies only fire down
	m_pBulletManager->fire( getPosition(), BulletDir::Down );
	m_fireIsReady = false;
	m_fireTimer = 0.0f;

	m_pFireSound->play();
}

void Enemy::setToFire()
{
	m_fireIsReady = true;
}

bool Enemy::isReadyToFire()
{
	return m_fireIsReady;
}

bool Enemy::fireRangeCheck()
{
	Player& player = m_pCollidableManager->getPlayer();

	// Using a player ref to check if it's within these x bounds to allow the enemy to shoot
	if( ( getPosition().x + getTextureDimensions().x * 0.5f ) + k_enemyRangeOffset > ( player.getPosition().x - player.getGlobalBounds().width * 0.5f )
		&& ( getPosition().x - getTextureDimensions().x * 0.5f ) - k_enemyRangeOffset < ( player.getPosition().x + player.getGlobalBounds().width * 0.5f ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::diveBomb( float deltaTime )
{
	sf::Vector2f playerPos = m_pCollidableManager->getPlayer().getPosition();

	// First part of the diveBomb, enemy lerps to position above player
	if( !m_abovePlayer )
	{
		if( m_lerpYValue < 1.0f )
		{
			// Using rotation for looking at the player
			float rotation;
			rotation = Math::angleToTarget( getPosition(), playerPos );

			// Changing the temp variable's y value to be used for lerp
			playerPos.y -= k_enemyToPlayerYDive;

			m_lerpYValue += k_enemyDiveSpeed * deltaTime;

			// Lerping
			setPosition( Math::lerp( m_lerpStartPos, playerPos, m_lerpYValue ) );
			setRotation( rotation );
		}
		else
		{
			// Enemy has reached the pos above player, setting values for next part
			m_abovePlayer = true;
			m_lerpStartPos = getPosition();
			m_lerpYValue = 0.0f;
			m_lerpXValue = k_enemyLerpXDefault;
			m_lerpXOffset = 0.0f;
		}
	}
	else
	{
		if( m_lerpYValue < 1.0f )
		{
			float rotation;
			m_lerpStartPos.x = playerPos.x;

			m_lerpYValue += k_enemyDiveSpeed * deltaTime;
	
			// Lerping towards the player while using a wave function that lerps horizontally to mimic a waving dive effect
			setPosition( wave( deltaTime, Math::lerp( m_lerpStartPos, playerPos, m_lerpYValue ) ) );
			rotation = Math::angleToTarget( getPosition(), playerPos );
			setRotation( rotation );
		}
		else if( m_lerpYValue >= 1.0f )
		{
			// Enemy has reached the destination
			beginReturning();
		}
	}
}

void Enemy::startDiving()
{
	// Setting values needed for dive bomb
	m_currentState = EnemyState::Attacking;
	m_lerpStartPos = getPosition();
	m_waveLeft = Math::randomiseInt( 0, 1 );
}

const sf::Vector2f& Enemy::wave( float deltaTime, const sf::Vector2f& posToWaveFrom )
{
	// Setting up the positions needed for wave
	sf::Vector2f leftPos = posToWaveFrom;
	sf::Vector2f rightPos = posToWaveFrom;
	sf::Vector2f midPos = posToWaveFrom;

	leftPos.x -= k_enemyDiveXOffset;
	rightPos.x += k_enemyDiveXOffset;
	midPos.y -= k_enemyDiveYOffset;

	// Lerping back and forth based on m_waveLeft
	if( m_waveLeft )
	{
		m_lerpXValue -= k_enemyDiveWaveSpeed * deltaTime;

		if( m_lerpXValue < 0.0f )
		{
			m_waveLeft = false;
			m_lerpXValue = 0.0f;
		}
	}
	else
	{
		m_lerpXValue += k_enemyDiveWaveSpeed * deltaTime;

		if( m_lerpXValue >= 1.0f )
		{
			m_waveLeft = true;
			m_lerpXValue = 1.0f;
		}
	}

	// quadraticLerp based on the three positions set up with an easeInOut
	return Math::quadraticLerp( leftPos, midPos, rightPos, Math::easeInOut( m_lerpXValue ) );
}

void Enemy::destroy()
{
	// Destroys the enemy and plays an explosion sound
	m_pExplosionSound->play();
	setCurrentState( EnemyState::Inactive );
}

void Enemy::collisionCheck()
{
	// Getting refs to the needed objects for collision checking
	Player& player = m_pCollidableManager->getPlayer();
	BarrierManager& barrierManager = m_pCollidableManager->getBarrierManager();

	for( int i = 0; i < barrierManager.getBarrierAmount(); i++ )
	{
		Barrier& currentBarrier = barrierManager.getBarrierByIndex( i );
		if( currentBarrier.isActive() )
		{
			for( int j = 0; j < k_barrierHealth; j++ )
			{
				BarrierSegment& currentSegment = currentBarrier.getSegmentByIndex( j );
				if( currentSegment.isActive() )
				{
					// Barrier collision
					if( ( getPosition().x + getTextureDimensions().x * 0.5f ) > ( currentSegment.getPosition().x - currentSegment.getGlobalBounds().width * 0.5f )
						&& ( getPosition().x - getTextureDimensions().x * 0.5f ) < ( currentSegment.getPosition().x + currentSegment.getGlobalBounds().width * 0.5f )
						&& ( getPosition().y + getTextureDimensions().y * 0.5f ) > ( currentSegment.getPosition().y - currentSegment.getGlobalBounds().height * 0.5f )
						&& ( getPosition().y - getTextureDimensions().y * 0.5f ) < ( currentSegment.getPosition().y + currentSegment.getGlobalBounds().height * 0.5f ) )
					{
						// Destroying the barrier segment then destroying the enemy
						currentSegment.destroy();
						setCurrentState( EnemyState::Inactive );
						return;
					}
				}
			}
		}
	}

	// Player collision
	if( ( getPosition().x + getTextureDimensions().x * 0.5f ) > ( player.getPosition().x - player.getGlobalBounds().width * 0.5f )
		&& ( getPosition().x - getTextureDimensions().x * 0.5f ) < ( player.getPosition().x + player.getGlobalBounds().width * 0.5f )
		&& ( getPosition().y + getTextureDimensions().y * 0.5f ) > ( player.getPosition().y - player.getGlobalBounds().height * 0.5f )
		&& ( getPosition().y - getTextureDimensions().y * 0.5f ) < ( player.getPosition().y + player.getGlobalBounds().height * 0.5f ) )
	{
		// Telling the player to take damage, and then destroying the enemy
		player.takeDamage();
		setCurrentState( EnemyState::Inactive );
		return;
	}
}

const int Enemy::getScoreValue() const
{
	return m_scoreValue;
}

void Enemy::setScoreValue( const int value )
{
	m_scoreValue = value;
}

void Enemy::reset()
{
	// Resetting all values needed for a clean reset without reloading the state
	m_currentState = EnemyState::Inactive;
	m_lerpYValue = 0.0f;
	m_lerpXValue = 0.0f;
	m_lerpXOffset = 0.0f;
	m_lerpedXPos = 0.0f;
	m_formationFirstLerp = false;
	m_fireTimer = 0.0f;
	m_scoreValue = k_enemyScoreValue;
	m_fireIsReady = false;
	m_waveLeft = false;
}