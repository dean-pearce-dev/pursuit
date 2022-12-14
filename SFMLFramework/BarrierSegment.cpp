#include <SFML/Graphics/RenderWindow.hpp>
#include "BarrierSegment.h"
#include "Director.h"
#include "GameSound.h"
#include "Settings.h"
#include "SoundManager.h"
#include "ReferenceManager.h"
#include "TextureManager.h"
#include "Helpers.h"


BarrierSegment::BarrierSegment()
	: m_pWindow			( nullptr )
	, m_pExplosionSound	( nullptr )
	, m_isActive		( false )
{
}

BarrierSegment::~BarrierSegment()
{
	safeDelete( m_pExplosionSound );
}

void BarrierSegment::update( float deltaTime )
{

}

void BarrierSegment::draw()
{
	m_pWindow->draw( *this );
}

void BarrierSegment::init( const ReferenceManager& refManager, const int segmentNum )
{
	m_pWindow = &refManager.getWindowHandle();

	m_pExplosionSound = new GameSound();
	m_pExplosionSound->setBuffer( refManager.getSoundManager().getExplosion() );
	m_pExplosionSound->setVolume( refManager.getSoundManager().getFxVolume() );

	setCurrentTexture( refManager.getTextureManager().getBarrier() );

	setScale( k_barrierScale, k_barrierScale );

	// Getting dimensions to use bounds correctly
	setTextureDimensions( getGlobalBounds().width, getGlobalBounds().height );

	setupTextureCoords( segmentNum, k_barrierHealth, k_barrierSpriteColumns );

	m_isActive = true;
}

void BarrierSegment::enable()
{
	m_isActive = true;
}

void BarrierSegment::disable()
{
	m_isActive = false;
}

void BarrierSegment::destroy()
{
	disable();
	m_pExplosionSound->play();
}

bool BarrierSegment::isActive()
{
	return m_isActive;
}