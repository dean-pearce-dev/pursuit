#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

namespace sf
{
	class RenderWindow;
}

class Director;
class TextureManager;
class Background;

class BackgroundManager
{
private:
	sf::RenderWindow* m_pWindow;

	TextureManager* m_pTextureManager;

	Background* m_pBackground1;
	Background* m_pBackground2;

	float m_speed;

public:
	BackgroundManager();
	~BackgroundManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: update
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Updates the object
	//////////////////////////////////////////////////////////////////////
	void update( float deltaTime );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: draw
	/// Parameters: none
	/// Returns: void
	/// Purpose: Draws the object
	//////////////////////////////////////////////////////////////////////
	void draw();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: init
	/// Parameters: Director& director
	/// Returns: void
	/// Purpose: Initialises the object
	//////////////////////////////////////////////////////////////////////
	void init( Director& director );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: reset
	/// Parameters: none
	/// Returns: void
	/// Purpose: Resets the object
	//////////////////////////////////////////////////////////////////////
	void reset();
};

#endif // End of '#ifndef BACKGROUNDMANAGER_H'