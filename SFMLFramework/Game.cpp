#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Director.h"
#include "Enemy.h"
#include "GameState.h"
#include "Helpers.h"
#include "Player.h"
#include "MainMenuManager.h"
#include "StateManager.h"
#include "Settings.h"

Game::Game()
	: m_pWindow		( nullptr )
	, m_pClock		( nullptr )
	, m_pDirector	( nullptr )
{
	// Creating the window
	m_pWindow = new sf::RenderWindow( sf::VideoMode( k_windowWidth, k_windowHeight ), "Pursuit" );

	// Creating the clock
	m_pClock = new sf::Clock();

	m_pDirector = new Director();

	m_pDirector->init( *m_pWindow );
}

Game::~Game()
{
	// Safe deleting pointers
	safeDelete( m_pDirector );
	safeDelete( m_pClock );
	safeDelete( m_pWindow );
}

void Game::handleWindowsEvents()
{
	sf::Event event;
	while( m_pWindow->pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed )
		{
			m_pWindow->close();
		}
	}
}

void Game::run()
{
	while( m_pWindow->isOpen() )
	{
		// Handle all Windows events
		handleWindowsEvents();

		// Clear the Screen
		m_pWindow->clear();

		// Get the elapsedTime since last time round
		float elapsedTime = m_pClock->restart().asSeconds();

		// Update all objects
		update( elapsedTime );

		// Render all objects
		render();

		// Display all rendered objects
		m_pWindow->display();
	}
} 

void Game::update( float deltaTime )
{
	m_pDirector->update( deltaTime );
}

void Game::render()
{
	m_pDirector->draw();
}


