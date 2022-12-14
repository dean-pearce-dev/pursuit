#include "Helpers.h"
#include "FontManager.h"

FontManager::FontManager()
{

}

FontManager::~FontManager()
{

}

bool FontManager::load( const char* fontFileName, sf::Font& fontToSet )
{
	bool loaded = fontToSet.loadFromFile( fontFileName );
	ASSERT( loaded == true );

	return loaded;
}

void FontManager::loadMainFont()
{
	load( "assets/fonts/PressStart2P-Regular.ttf", m_mainFont );
}

const sf::Font& FontManager::getMainFont() const
{
	return m_mainFont;
}