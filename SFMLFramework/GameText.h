#ifndef GAMETEXT_H
#define GAMETEXT_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class GameText : public sf::Text
{
private:
	sf::Font m_font;

public:
	GameText();
	~GameText();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: init
	/// Parameters: const sf::Font& font, const sf::String& string, const int size = 32, const bool centerOrigin = true, const float outlineThickness = 1.0f
	/// Returns: void
	/// Purpose: initiailises the GameText and uses the paramaters to set the font, string, size, whether the origin should be centered, and the outline thickness
	//////////////////////////////////////////////////////////////////////
	void init( const sf::Font& font, const sf::String& string, const int size = 32, const bool centerOrigin = true, const float outlineThickness = 1.0f );
};

#endif // End of '#ifndef GAMETEXT_H'