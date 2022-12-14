#include <SFML/Graphics/RenderWindow.hpp>

#include "Background.h"
#include "Helpers.h"
#include "Settings.h"

Background::Background()
	: m_pWindow	( nullptr )
	, m_speed	( k_bgSpeed )
{

}


Background::~Background()
{
}

void Background::update( float deltaTime )
{
	sf::Vector2f pos = getPosition();

	// Checking if the background has moved past the bottom of the screen
	if( pos.y > k_arenaHeight + ( m_textureDimensions.y / 2 ) )
	{
		// Setting the y position to be above the screen to allow a seamless transition with the second background
		pos.y = m_textureDimensions.y / 2 - k_arenaHeight;
		setPosition( pos );
	}

	move( 0.0f, m_speed * deltaTime );
}

void Background::draw()
{
	m_pWindow->draw( *this );
}

void Background::init( sf::RenderWindow& windowHandle, const sf::Texture& textureToSet )
{
	m_pWindow = &windowHandle;

	setCurrentTexture( textureToSet );

	//setScale( 1.0f, 1.0f );

	// Getting dimensions to use bounds correctly
	m_textureDimensions.x = getGlobalBounds().width;
	m_textureDimensions.y = getGlobalBounds().height;

	// Setting initial position
	setPosition( k_arenaWidth / 2, m_textureDimensions.y / 2 );
}