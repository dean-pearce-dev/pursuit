#include "Helpers.h"
#include "GameText.h"

GameText::GameText()
{
}

GameText::~GameText()
{

}

void GameText::init( const sf::Font& font, const sf::String& string, const int size, const bool centerOrigin, const float outlineThickness )
{
	// Setting font, string, size, and outline thickness
	setFont( font );
	setString( string );
	setCharacterSize( size );
	setOutlineThickness( outlineThickness );

	// Setting the origin
	sf::FloatRect stringRect = getLocalBounds();
	if ( centerOrigin )
	{
		setOrigin( stringRect.left + stringRect.width / 2.0f, stringRect.top + stringRect.height / 2.0f );
	}
}