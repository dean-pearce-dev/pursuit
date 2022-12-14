#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SFML/Graphics/Font.hpp>

class FontManager
{
private:
	sf::Font m_mainFont;

public:
	FontManager();
	~FontManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: load
	/// Parameters: const char* fontFileName, sf::Font& fontToSet
	/// Returns: bool
	/// Purpose: Loads a font
	//////////////////////////////////////////////////////////////////////
	bool load( const char* fontFileName, sf::Font& fontToSet );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: loadMainFont
	/// Parameters: none
	/// Returns: void
	/// Purpose: Loads the main font that will be used by the game
	//////////////////////////////////////////////////////////////////////
	void loadMainFont();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getMainFont
	/// Parameters: none
	/// Returns: const sf::Font&
	/// Purpose: Returns a reference to the main font
	//////////////////////////////////////////////////////////////////////
	const sf::Font& getMainFont() const;
};

#endif // End of '#ifndef FONTMANAGER_H'
