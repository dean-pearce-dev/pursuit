#ifndef PAUSEMANAGER_H
#define PAUSEMANAGER_H

#include "PauseState.h"

namespace sf
{
	class RenderWindow;
}

class ReferenceManager;
class GameplayDirector;
class GameSound;
class GameText;
class FontManager;
class InputManager;
class SoundManager;
class StateManager;

class PauseManager
{
private:
	sf::RenderWindow* m_pWindow;

	FontManager* m_pFontManager;

	InputManager* m_pInputManager;

	StateManager* m_pStateManager;

	SoundManager* m_pSoundManager;

	GameplayDirector* m_pGameplayDirector;

	GameText* m_pPauseElementsArray;

	GameText* m_pSelectedElement;

	GameText* m_pOptionsElementsArray;

	GameSound* m_pMenuMoveSound;
	GameSound* m_pMenuConfirmSound;
	GameSound* m_pMenuDenySound;

	PauseState m_pauseState;

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
	bool m_enterIsPressed;
	bool m_escIsPressed;

	bool m_shouldReturnToMenu;

public:
	PauseManager();
	~PauseManager();

	void update( float deltaTime );
	void draw();

	void init( const ReferenceManager& refManager );

	void pausedUpdate( float deltaTime );

	void initOptionsScreen();
	void optionsUpdate( float deltaTime );

	void resetVolume();
	void resetOptionStrings();

	void selectedElementAnim( float deltaTime );

	bool shouldReturnToMenu();
};

#endif // End of '#ifndef PAUSEMANAGER_H'