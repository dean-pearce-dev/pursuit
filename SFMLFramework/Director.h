#ifndef	DIRECTOR_H
#define DIRECTOR_H

#include "GameState.h"

namespace sf
{
	class RenderWindow;
}

class BackgroundManager;
class BarrierManager;
class FontManager;
class GameplayDirector;
class HiScoreManager;
class InputManager;
class MainMenuManager;
class ReferenceManager;
class SoundManager;
class StateManager;
class TextureManager;

class Director
{
private:
	sf::RenderWindow* m_pWindow;

	StateManager* m_pStateManager;

	TextureManager* m_pTextureManager;

	MainMenuManager* m_pMainMenuManager;

	BackgroundManager* m_pBackgroundManager;

	BarrierManager* m_pBarrierManager;

	FontManager* m_pFontManager;

	HiScoreManager* m_pHiScoreManager;

	InputManager* m_pInputManager;

	GameplayDirector* m_pGameplayDirector;

	ReferenceManager* m_pReferenceManager;

	SoundManager* m_pSoundManager;

	bool m_isPausePressed;

public:
	Director();
	~Director();

	/////////////////////////////////////////////////////////////////////
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
	/// Parameters: sf::RenderWindow& windowHandle
	/// Returns: void
	/// Purpose: Initialises the object
	//////////////////////////////////////////////////////////////////////
	void init( sf::RenderWindow& windowHandle );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: initState
	/// Parameters: GameState stateToInit
	/// Returns: void
	/// Purpose: Initialises the state based on the parameter
	//////////////////////////////////////////////////////////////////////
	void initState( GameState stateToInit );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: uninitState
	/// Parameters: none
	/// Returns: void
	/// Purpose: Uninitialises the state
	//////////////////////////////////////////////////////////////////////
	void uninitState();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: changeState
	/// Parameters: const GameState stateToChange
	/// Returns: void
	/// Purpose: Changes the state using initState and uninitState
	//////////////////////////////////////////////////////////////////////
	void changeState( const GameState stateToChange );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getWindowHandle
	/// Parameters: none
	/// Returns: sf::RenderWindow&
	/// Purpose: Returns a reference to the window handle
	//////////////////////////////////////////////////////////////////////
	sf::RenderWindow& getWindowHandle();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getStateManager
	/// Parameters: none
	/// Returns: StateManager&
	/// Purpose: Returns a reference to the state manager
	//////////////////////////////////////////////////////////////////////
	StateManager& getStateManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getTextureManager
	/// Parameters: none
	/// Returns: TextureManager&
	/// Purpose: Returns a reference to the texture manager
	//////////////////////////////////////////////////////////////////////
	TextureManager& getTextureManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getMainMenuManager
	/// Parameters: none
	/// Returns: MainMenuManager&
	/// Purpose: Returns a reference to the main menu manager
	//////////////////////////////////////////////////////////////////////
	MainMenuManager& getMainMenuManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getBackgroundManager
	/// Parameters: none
	/// Returns: BackgroundManager&
	/// Purpose: Returns a reference to the background manager
	//////////////////////////////////////////////////////////////////////
	BackgroundManager& getBackgroundManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getBarrierManager
	/// Parameters: none
	/// Returns: BarrierManager&
	/// Purpose: Returns a reference to the barrier manager
	//////////////////////////////////////////////////////////////////////
	BarrierManager& getBarrierManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getFontManager
	/// Parameters: none
	/// Returns: FontManager&
	/// Purpose: Returns a reference to the font manager
	//////////////////////////////////////////////////////////////////////
	FontManager& getFontManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getHiScoreManager
	/// Parameters: none
	/// Returns: HiScoreManager&
	/// Purpose: Returns a reference to the hi score manager
	//////////////////////////////////////////////////////////////////////
	HiScoreManager& getHiScoreManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getInputManager
	/// Parameters: none
	/// Returns: InputManager&
	/// Purpose: Returns a reference to the input manager
	//////////////////////////////////////////////////////////////////////
	InputManager& getInputManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getGameplayDirector
	/// Parameters: none
	/// Returns: GameplayDirector&
	/// Purpose: Returns a reference to the gameplay director
	//////////////////////////////////////////////////////////////////////
	GameplayDirector& getGameplayDirector();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getSoundManager
	/// Parameters: none
	/// Returns: SoundManager&
	/// Purpose: Returns a reference to the sound manager
	//////////////////////////////////////////////////////////////////////
	SoundManager& getSoundManager();
};

#endif // End of '#ifndef DIRECTOR_H'