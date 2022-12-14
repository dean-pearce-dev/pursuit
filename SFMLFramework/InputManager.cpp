#include <SFML/Window/Keyboard.hpp>

#include "InputManager.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

bool InputManager::upIsPressed()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ||
		sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool InputManager::downIsPressed()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ||
		sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool InputManager::leftIsPressed()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ||
		sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool InputManager::rightIsPressed()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ||
		sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool InputManager::spaceIsPressed()
{
	return sf::Keyboard::isKeyPressed( sf::Keyboard::Space );
}

bool InputManager::enterIsPressed()
{
	return sf::Keyboard::isKeyPressed( sf::Keyboard::Enter );
}

bool InputManager::escIsPressed()
{
	return sf::Keyboard::isKeyPressed( sf::Keyboard::Escape );
}

bool InputManager::pIsPressed()
{
	return sf::Keyboard::isKeyPressed( sf::Keyboard::P );
}