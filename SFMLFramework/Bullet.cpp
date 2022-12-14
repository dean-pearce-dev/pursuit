#include "Bullet.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Settings.h"

Bullet::Bullet()
	: m_pCollidableManager	( nullptr )
	, m_speed				( k_defaultBulletSpeed )
	, m_isActive			( false )
	, m_currentDir			( BulletDir::Up )
{
}

Bullet::~Bullet()
{

}

void Bullet::update( float deltaTime )
{
}

void Bullet::init( const sf::Texture& textureToSet )
{
	setCurrentTexture( textureToSet );
	setScale( k_defaultBulletScale, k_defaultBulletScale );

	// Getting dimensions to use bounds correctly
	setTextureDimensions( getGlobalBounds().width, getGlobalBounds().height );

	// Setting initial position
	setPosition( -getTextureDimensions() );
}

bool Bullet::isActive()
{
	return m_isActive;
}

void Bullet::setActive( bool setActive )
{
	m_isActive = setActive;
}

void Bullet::collisionCheck()
{
}

void Bullet::setCollidableManager( CollidableManager& collidableManager )
{
	m_pCollidableManager = &collidableManager;
}

CollidableManager& Bullet::getCollidableManager()
{
	return *m_pCollidableManager;
}

float Bullet::getSpeed()
{
	return m_speed;
}

const BulletDir Bullet::getDir() const
{
	return m_currentDir;
}

void Bullet::setDir( BulletDir direction )
{
	m_currentDir = direction;
}

// Resets the bullet
void Bullet::disable()
{
	m_isActive = false;
}