#ifndef MAINMENUMANAGER_H
#define MAINMENUMANAGER_H

#include "GameState.h"
#include "MenuState.h"

namespace sf
{
	class RenderWindow;
}

class Director;
class Credits;
class GameSound;
class GameText;
class FontManager;
class HiScoreManager;
class InputManager;
class SoundManager;

class MainMenuManager
{
private:
	sf::RenderWindow* m_pWindow;

	FontManager* m_pFontManager;

	HiScoreManager* m_pHiScoreManager;

	InputManager* m_pInputManager;

	SoundManager* m_pSoundManager;

	GameText* m_pMenuElementsArray;

	GameText* m_pSelectedElement;

	GameText* m_pFxVolumeText;
	GameText* m_pMusicVolumeText;
	GameText* m_pBackText;
	GameText* m_pOptionsElementsArray;

	GameText* m_pHighScoresText;
	GameText* m_pInitialsArray;
	GameText* m_pScoresArray;

	GameSound* m_pMenuMoveSound;
	GameSound* m_pMenuConfirmSound;
	GameSound* m_pMenuDenySound;
	GameSound* m_pMenuMusic;

	Credits* m_pCredits;

	MenuState m_menuState;

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

	bool m_shouldGameStart;

public:
	MainMenuManager();
	~MainMenuManager();

	void update( float deltaTime );
	void draw();

	void init( Director& director );

	void initMenuScreen();

	void initLeaderboardScreen();
	void initOptionsScreen();

	void menuUpdate( float deltaTime );
	void leaderboardUpdate( float deltaTime );
	void optionsUpdate( float deltaTime );

	void resetVolume();
	void resetOptionStrings();

	void selectedElementAnim( float deltaTime );

	bool shouldGameStart();
};

#endif // End of '#ifndef MAINMENUMANAGER_H'
