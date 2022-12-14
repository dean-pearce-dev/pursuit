#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameSprite.h"

namespace sf
{
	class RenderWindow;
}

class Background : public GameSprite
{
private:
	sf::Vector2f m_textureDimensions;

	sf::RenderWindow* m_pWindow;

	float m_speed;

public:
	Background();
	~Background();

	void update( float deltaTime );
	void draw();

	void init( sf::RenderWindow& windowHandle, const sf::Texture& textureToSet );
};

#endif // End of '#ifndef BACKGROUND_H'