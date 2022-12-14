#include <iostream>

#include "Helpers.h"
#include "GameSprite.h"

GameSprite::GameSprite()
	: m_textureDimensions ( sf::Vector2f( 0, 0 ) )
{

}

GameSprite::~GameSprite()
{

}

void GameSprite::setCurrentTexture( const sf::Texture& textureToSet )
{
	// Setting the texture via the base class
	setTexture( textureToSet );

	// Set the origin of the sprite to be the center
	sf::Vector2u textureDimensions = textureToSet.getSize();
	setOrigin(	static_cast< float >( textureDimensions.x / 2 ),
				static_cast< float >( textureDimensions.y / 2 ) );
}

void GameSprite::setTextureDimensions( float x, float y )
{
	m_textureDimensions = sf::Vector2f( x, y );
}

const sf::Vector2f& GameSprite::getTextureDimensions()
{
	return m_textureDimensions;
}

void GameSprite::setupTextureCoords( const int frameNum, const int rows, const int columns )
{
	// Getting the texture and size to work from
	const sf::Texture& texture = *getTexture();
	sf::Vector2u dimensions = texture.getSize();

	// Dividing the width and height into a grid defined by rows and columns
	int frameWidth = dimensions.x / columns;
	int frameHeight = dimensions.y / rows;

	// Finding the grid position via frameNum
	int targetColumn = frameNum % columns;
	int targetRow = static_cast<int>( std::floor( frameNum / columns ) );

	// Usinf sf::IntRect to set the rect of the texture to be used
	sf::IntRect rect;
	rect.left = frameWidth * targetColumn;
	rect.top = frameHeight * targetRow;
	rect.width = frameWidth;
	rect.height = frameHeight;

	setTextureRect( rect );
}
