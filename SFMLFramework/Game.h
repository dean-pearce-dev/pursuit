#ifndef GAME_H
#define GAME_H

namespace sf
{
	class RenderWindow;
	class Clock;
}

class Director;

enum class InGameState;

class Game
{
private:
	sf::RenderWindow*	m_pWindow;
	sf::Clock*			m_pClock;

	Director*			m_pDirector;

	void handleWindowsEvents();

	void update( float deltaTime );
	void render();

	void changeState( const InGameState stateToChange );

	void onEnterState( const InGameState stateToEnter );
	void onLeaveState();

public:
	Game();
	~Game();

	void run();

};

#endif // End of '#ifndef GAME_H'
