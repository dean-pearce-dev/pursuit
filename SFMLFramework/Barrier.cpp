#include <SFML/Graphics/RenderWindow.hpp>

#include "Barrier.h"
#include "BarrierSegment.h"
#include "Director.h"
#include "Helpers.h"
#include "Settings.h"
#include "SoundManager.h"
#include "TextureManager.h"

Barrier::Barrier()
	: m_pSegmentArray	( nullptr )
	, m_isActive		( false )
{
}

Barrier::~Barrier()
{
	safeDeleteArray( m_pSegmentArray );
}

void Barrier::update( float deltaTime )
{
	if( !segmentCheck() )
	{
		disable();
	}

	for( int i = 0; i < k_barrierHealth; i++ )
	{
		if( m_pSegmentArray[i].isActive() )
		{
			m_pSegmentArray[i].update( deltaTime );
		}
	}
}

void Barrier::draw()
{
	for( int i = 0; i < k_barrierHealth; i++ )
	{
		if( m_pSegmentArray[i].isActive() )
		{
			m_pSegmentArray[i].draw();
		}
	}
}

void Barrier::init( const ReferenceManager& refManager )
{
	m_pSegmentArray = new BarrierSegment[k_barrierHealth];

	for( int i = 0; i < k_barrierHealth; i++ )
	{
		m_pSegmentArray[i].init( refManager, i );
	}
	m_isActive = true;
}

void Barrier::reset()
{
	for( int i = 0; i < k_barrierHealth; i++ )
	{
		m_pSegmentArray[i].enable();
	}
	m_isActive = true;
}

void Barrier::disable()
{
	m_isActive = false;
}

bool Barrier::isActive()
{
	return m_isActive;
}

bool Barrier::segmentCheck()
{
	bool isSegmentsRemaining = false;

	for( int i = 0; i < k_barrierHealth; i++ )
	{
		if( m_pSegmentArray[i].isActive() )
		{
			isSegmentsRemaining = true;
		}
	}

	return isSegmentsRemaining;
}

BarrierSegment& Barrier::getSegmentByIndex( const int index )
{
	return m_pSegmentArray[index];
}

const sf::Vector2f& Barrier::getPosition()
{
	return m_position;
}

void Barrier::setPosition( const sf::Vector2f& position )
{
	m_position = position;
	sf::Vector2f segmentPosition = position;
	for( int i = 0; i < k_barrierHealth; i++ )
	{
		segmentPosition.y = position.y + ( m_pSegmentArray[i].getGlobalBounds().height * i );
		m_pSegmentArray[i].setPosition( segmentPosition );
	}
}