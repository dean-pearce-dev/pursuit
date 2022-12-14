#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Player.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "GameSound.h"
#include "ReferenceManager.h"
#include "SoundManager.h"
#include "WaveManager.h"
#include "Helpers.h"
#include "Settings.h"

// Default ctor
Player::Player()
	: m_pWindow				( nullptr )
	, m_pTextureManager		( nullptr )
	, m_pBulletManager		( nullptr )
	, m_pInputManager		( nullptr )
	, m_pWaveManager		( nullptr )
	, m_pFireSound			( nullptr )
	, m_pLoseLifeSound		( nullptr )
	, m_pExplosionSound		( nullptr )
	, m_currentState		( PlayerState::Inactive )
	, m_invulnTimer			( 0.0f )
	, m_flashTimer			( 0.0f )
	, m_tiltAngle			( k_playerTiltAngle )
	, m_lives				( k_playerLives )
	, m_score				( 0 )
	, m_isFiring			( false )
	, m_isAiming			( false )
	, m_isVisible			( true )
{
}

// Destructor
Player::~Player()
{
	safeDelete( m_pBulletManager );
	safeDelete( m_pFireSound );
	safeDelete( m_pLoseLifeSound );
	safeDelete( m_pExplosionSound );
}

void Player::update( float deltaTime )
{
	switch( m_currentState )
	{
		case PlayerState::Respawning:
		{
		}
		break;
		case PlayerState::Playing: case PlayerState::Damaged: case PlayerState::Invulnerable:
		{
			if( !m_isAiming )
			{
				move( deltaTime );
				if( m_pInputManager->spaceIsPressed() )
				{
					fire( BulletDir::Up );
				}
			}
			else
			{
				if( m_pInputManager->spaceIsPressed() )
				{
					aim();
				}
			}

			if( m_currentState == PlayerState::Damaged )
			{
				flashAnim( deltaTime );
			}
		}
		break;
		case PlayerState::Idle:
		{
			move( deltaTime );
		}
		break;
	}

	m_isAiming = m_pInputManager->downIsPressed();
	m_isFiring = m_pInputManager->spaceIsPressed();
	m_pBulletManager->update( deltaTime );
}

void Player::draw()
{
	m_pBulletManager->draw();

	if( m_isVisible && m_currentState != PlayerState::Inactive )
	{
		m_pWindow->draw( *this );
	}
}

void Player::move( float deltaTime )
{
	sf::Vector2f pos = getPosition();
	float rot = 0.0f;

	// Left Input
	if( m_pInputManager->leftIsPressed() )
	{
		pos.x -= k_playerMoveSpeed * deltaTime;
		rot = -m_tiltAngle;
		// Clamping player pos
		if( pos.x < getTextureDimensions().x / 2 )
		{
			pos.x = getTextureDimensions().x / 2;
			rot = 0.0f;
		}
	}

	// Right Input
	if( m_pInputManager->rightIsPressed() )
	{
		pos.x += k_playerMoveSpeed * deltaTime;
		rot = m_tiltAngle;

		// Clamping player pos
		if( pos.x > k_arenaWidth - ( getTextureDimensions().x / 2 ) )
		{
			pos.x = k_arenaWidth - ( getTextureDimensions().x / 2 );
			rot = 0.0f;
		}
	}

	setPosition( pos );
	setRotation( rot );
}

void Player::init( const ReferenceManager& refManager )
{
	m_pWindow = &refManager.getWindowHandle();
	m_pInputManager = &refManager.getInputManager();
	m_pWaveManager = &refManager.getWaveManager();

	m_pFireSound = new GameSound();
	m_pLoseLifeSound = new GameSound();
	m_pExplosionSound = new GameSound();

	m_pFireSound->setBuffer( refManager.getSoundManager().getFire() );
	m_pFireSound->setVolume( refManager.getSoundManager().getFxVolume() );
	m_pLoseLifeSound->setBuffer( refManager.getSoundManager().getLoseLife() );
	m_pLoseLifeSound->setVolume( refManager.getSoundManager().getFxVolume() );
	m_pExplosionSound->setBuffer( refManager.getSoundManager().getExplosion() );
	m_pExplosionSound->setVolume( refManager.getSoundManager().getFxVolume() );

	setCurrentTexture( refManager.getTextureManager().getPlayerShip() );
	setScale( k_playerScaleX, k_playerScaleY );

	// Getting dimensions to use bounds correctly
	setTextureDimensions( getGlobalBounds().width, getGlobalBounds().height );

	// Setting initial position
	setPosition( k_arenaWidth / 2 , k_arenaHeight - getTextureDimensions().y );

	m_pBulletManager = new BulletManager();
	m_pBulletManager->init( refManager );
	m_pBulletManager->initPlayerBullets();

	m_currentState = PlayerState::Idle;
}

void Player::fire( const BulletDir direction )
{
	if( !m_isFiring && m_pWaveManager->getState() == WaveState::InProgress && m_pBulletManager->canFire() )
	{
		m_isFiring = true;
		switch( direction )
		{
			case BulletDir::Up:
			{
				m_pBulletManager->fire( getPosition(), BulletDir::Up );
			}
			break;
			case BulletDir::UpLeft:
			{
				m_pBulletManager->fire( getPosition(), BulletDir::UpLeft );
			}
			break;
			case BulletDir::UpRight:
			{
				m_pBulletManager->fire( getPosition(), BulletDir::UpRight );
			}
			break;
		}
		m_pFireSound->play();
	}
}

void Player::aim()
{
	if( m_pInputManager->leftIsPressed() )
	{
		fire( BulletDir::UpLeft );
	}

	else if( m_pInputManager->rightIsPressed() )
	{
		fire( BulletDir::UpRight );
	}

}

void Player::flashAnim( float deltaTime )
{
	if( m_invulnTimer < k_playerInvulnTime )
	{
		m_invulnTimer += deltaTime;
		if( m_flashTimer < k_playerFlashAnimTime )
		{
			m_flashTimer += deltaTime;
		}
		else
		{
			m_flashTimer = 0.0f;
			m_isVisible = !m_isVisible;
		}
	}
	else
	{
		m_invulnTimer = 0.0f;
		m_flashTimer = 0.0f;
		m_isVisible = true;
		setColor( k_playerDefaultColor );
		m_currentState = PlayerState::Playing;
	}
}

void Player::takeDamage()
{
	m_pExplosionSound->play();

	if( !isInvuln() )
	{
		m_pLoseLifeSound->play();
		m_currentState = PlayerState::Damaged;
		setColor( k_playerDamagedColor );
		m_lives--;
		if( m_lives == 0 )
		{
			setColor( k_playerDefaultColor );
			setState( PlayerState::Inactive );
		}
	}
}

PlayerState Player::getState()
{
	return m_currentState;
}

void Player::setState( const PlayerState stateToSet )
{
	m_currentState = stateToSet;
}

bool Player::isInvuln()
{
	return m_currentState != PlayerState::Playing;
}

void Player::addScore( const int scoreToAdd )
{
	m_score += scoreToAdd;
}

const int Player::getLives() const
{
	return m_lives;
}

const int Player::getScore() const
{
	return m_score;
}

int Player::getRemainingBullets()
{
	return k_playerMaxFiredBullets - m_pBulletManager->getFiredBullets();
}

void Player::reset()
{
	m_lives = k_playerLives;
	m_score = 0;
	setPosition( k_arenaWidth / 2, k_arenaHeight - getTextureDimensions().y );
	m_currentState = PlayerState::Idle;
	setColor( k_playerDefaultColor );
	m_isVisible = true;
	m_pBulletManager->reset();
}