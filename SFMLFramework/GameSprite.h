#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class GameSprite : public sf::Sprite
{
private:
	sf::Texture m_texture;

	sf::Vector2f m_textureDimensions;

public:
	GameSprite();
	virtual ~GameSprite();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: setCurrentTexture
	/// Parameters: const sf::Texture& textureToSet
	/// Returns: void
	/// Purpose: Sets the GameSprite's texture and centers the origin
	//////////////////////////////////////////////////////////////////////
	virtual void setCurrentTexture( const sf::Texture& textureToSet );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: setTextureDimensions
	/// Parameters: float x, float y
	/// Returns: void
	/// Purpose: Sets the dimensions of the texture by x and y float paramaters
	//////////////////////////////////////////////////////////////////////
	void setTextureDimensions( float x, float y );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getTextureDimensions
	/// Parameters: none
	/// Returns: const sf::Vector2f&
	/// Purpose: Returns the dimensions via a const sf::Vector2f reference
	//////////////////////////////////////////////////////////////////////
	const sf::Vector2f& getTextureDimensions();

	//////////////////////////////////////////////////////////////////////
	///	Function/Functions: setupTextureCoords
	///	Parameters: const int frameNum, const int rows, const int columns
	///	Returns: void
	/// Purpose: Sets the portion of the texture to be used by given frame num,
	///			 calculated by how many rows and columns the texture should be divided into
	//////////////////////////////////////////////////////////////////////
	void setupTextureCoords( const int frameNum, const int rows, const int columns );
};

#endif // End of '#ifndef GAMESPRITE_H'