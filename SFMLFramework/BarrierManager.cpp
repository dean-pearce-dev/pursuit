#include <SFML/Graphics/RenderWindow.hpp>

#include "BarrierManager.h"
#include "TextureManager.h"
#include "Barrier.h"
#include "Director.h"
#include "Helpers.h"
#include "ReferenceManager.h"
#include "Settings.h"

BarrierManager::BarrierManager()
	: m_pWindow			( nullptr )
	, m_pTextureManager	( nullptr )
	, m_pBarrierArray	( nullptr )
{
}

BarrierManager::~BarrierManager()
{
	safeDeleteArray( m_pBarrierArray );
}

void BarrierManager::update( float deltaTime )
{
	for( int i = 0; i < k_barrierNum; i++ )
	{
		if ( m_pBarrierArray[i].isActive() )
		{ 
			m_pBarrierArray[i].update( deltaTime );
		}
	}
}

void BarrierManager::draw()
{
	for( int i = 0; i < k_barrierNum; i++ )
	{
		if( m_pBarrierArray[i].isActive() )
		{
			m_pBarrierArray[i].draw();
		}
	}
}

void BarrierManager::init( const ReferenceManager& refManager )
{
	m_pWindow = &refManager.getWindowHandle();
	m_pTextureManager = &refManager.getTextureManager();

	// Making array with k_barrierNum
	m_pBarrierArray = new Barrier[k_barrierNum];

	// Figuring out the space the barrier uses
	float barrierSpacing = static_cast<float>( k_windowWidth / ( k_barrierNum + 1 ) );
	int barrierNumHalf = k_barrierNum / 2;

	// Checking for odd to add 1 since divided ints round towards 0
	if( k_barrierNum % 2 )
	{
		barrierNumHalf += 1;
	}

	for( int i = 0; i < k_barrierNum; i++ )
	{
		// Setting barriers into position
		int diffFromHalf = barrierNumHalf - ( i + 1 );
		m_pBarrierArray[i].init( refManager );
		m_pBarrierArray[i].setPosition( sf::Vector2f(( barrierSpacing * ( i + 1 ) ) - ( k_gapBetweenBarriers * diffFromHalf ), k_barrierHeight ) );
	}
}

Barrier& BarrierManager::getBarrierByIndex( const int index )
{
	return m_pBarrierArray[index];
}

const int BarrierManager::getBarrierAmount()
{
	return k_barrierNum;
}

void BarrierManager::reset()
{
	for( int i = 0; i < k_barrierNum; i++ )
	{
		m_pBarrierArray[i].reset();
	}
}