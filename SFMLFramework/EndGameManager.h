#ifndef ENDGAMEMANAGER_H
#define ENDGAMEMANAGER_H

class FontManager;
class GameplayDirector;
class GameSound;
class GameText;
class HiScoreManager;
class InputManager;
class Player;
class ReferenceManager;
class StateManager;

class EndGameManager
{
private:
	sf::RenderWindow* m_pWindow;

	FontManager* m_pFontManager;

	InputManager* m_pInputManager;

	StateManager* m_pStateManager;

	GameplayDirector* m_pGameplayDirector;

	HiScoreManager* m_pHiScoreManager;

	Player* m_pPlayer;

	GameText* m_pEndElementsArray;

	GameText* m_pSelectedElement;

	GameText* m_pYouScoredText;
	GameText* m_pGameOverText;
	GameText* m_pVictoryText;

	GameText* m_pHighScoresText;
	GameText* m_pEnterInitialsText;
	GameText* m_pNewHiScoreText;
	GameText* m_pInitialsScoreText;
	GameText* m_pContinueText;

	GameText* m_pInitialsArray;
	GameText* m_pScoresArray;

	GameText* m_pInitialsInputArray;

	GameSound* m_pMenuMoveSound;
	GameSound* m_pMenuConfirmSound;
	GameSound* m_pMenuDenySound;

	int m_selectedElementNum;

	float m_animScale;
	float m_animScaleDefault;
	float m_animScaleSpeed;
	float m_animScaleOffset;

	bool m_animScaleIncrease;

	bool m_upIsPressed;
	bool m_downIsPressed;
	bool m_leftIsPressed;
	bool m_rightIsPressed;
	bool m_escIsPressed;
	bool m_enterIsPressed;

	bool m_shouldReturnToMenu;


public:
	EndGameManager();
	~EndGameManager();

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
	/// Parameters: 
	/// Returns: void
	/// Purpose: Initialises the object
	//////////////////////////////////////////////////////////////////////
	void init( const ReferenceManager& refManager );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: hiScoreScreen, endScreen
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Updates the game for the specified state
	//////////////////////////////////////////////////////////////////////
	void hiScoreScreen( float deltaTime );
	void endScreen( float deltaTime );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: drawElementsArray
	/// Parameters: none
	/// Returns: void
	/// Purpose: Draw the menu elements
	//////////////////////////////////////////////////////////////////////
	void drawElementsArray();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: selectedElementAnim
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Animates the selected menu element
	//////////////////////////////////////////////////////////////////////
	void selectedElementAnim( float deltaTime );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: setupEndScreen, setupScoreScreen, setupHiScoreInputScreen
	/// Parameters: const ReferenceManager& refManager
	/// Returns: void
	/// Purpose: Sets up the state specified in the function name
	//////////////////////////////////////////////////////////////////////
	void setupEndScreen( const ReferenceManager& refManager );
	void setupScoreScreen( const ReferenceManager& refManager );
	void setupHiScoreInputScreen( const ReferenceManager& refManager );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getNewScores
	/// Parameters: none
	/// Returns: void
	/// Purpose: Retrieves the scores from hi score manager to be displayed on the scoreboard
	//////////////////////////////////////////////////////////////////////
	void getNewScores();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: goToEnterScore
	/// Parameters: none
	/// Returns: void
	/// Purpose: Go to the enter score state
	//////////////////////////////////////////////////////////////////////
	void goToEnterScore();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: shouldReturnToMenu
	/// Parameters: none
	/// Returns: bool
	/// Purpose: Returns whether the game should return to menu or not
	//////////////////////////////////////////////////////////////////////
	bool shouldReturnToMenu();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: resetScoreStrings
	/// Parameters: none
	/// Returns: void
	/// Purpose: Resets the score strings used to display the scores
	//////////////////////////////////////////////////////////////////////
	void resetScoreStrings();
};

#endif // End of '#ifndef ENDGAMEMANAGER_H'