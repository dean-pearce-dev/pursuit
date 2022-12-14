#ifndef GAMEPLAYDIRECTOR_H
#define GAMEPLAYDIRECTOR_H

namespace sf
{
	class RenderWindow;
}

class BackgroundManager;
class BarrierManager;
class CollidableManager;
class Director;
class EndGameManager;
class EnemyManager;
class FontManager;
class GameSound;
class InputManager;
class HiScoreManager;
class HudManager;
class PauseManager;
class ReferenceManager;
class SoundManager;
class StateManager;
class TextureManager;
class WaveManager;
class Player;

class GameplayDirector
{
private:
	BackgroundManager* m_pBackgroundManager;
	BarrierManager* m_pBarrierManager;
	CollidableManager* m_pCollidableManager;
	EnemyManager* m_pEnemyManager;
	HudManager* m_pHudManager;
	HiScoreManager* m_pHiScoreManager;
	PauseManager* m_pPauseManager;
	EndGameManager* m_pEndGameManager;
	SoundManager* m_pSoundManager;
	StateManager* m_pStateManager;
	WaveManager* m_pWaveManager;
	Player* m_pPlayer;

	GameSound* m_pGameMusic;

	bool m_shouldReturnToMenu;

public:
	GameplayDirector();
	~GameplayDirector();

	void update( float deltaTime );
	void draw();

	void init( ReferenceManager& refManager );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: playMusic
	/// Parameters: none
	/// Returns: void
	/// Purpose: Plays the game music
	//////////////////////////////////////////////////////////////////////
	void playMusic();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: pauseMusic
	/// Parameters: none
	/// Returns: void
	/// Purpose: Pauses the game music
	//////////////////////////////////////////////////////////////////////
	void pauseMusic();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: shouldReturnToMenu
	/// Parameters: none
	/// Returns: bool
	/// Purpose: Returns whether the game director should return to menu
	//////////////////////////////////////////////////////////////////////
	bool shouldReturnToMenu();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: playerIsDefeated
	/// Parameters: none
	/// Returns: bool
	/// Purpose: Returns whether the player is defeated
	//////////////////////////////////////////////////////////////////////
	bool playerIsDefeated();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: resetGame
	/// Parameters: none
	/// Returns: void
	/// Purpose: Resets the game to be played again without reloading the game
	//////////////////////////////////////////////////////////////////////
	void resetGame();

	BackgroundManager& getBackgroundManager();
	BarrierManager& getBarrierManager();
	CollidableManager& getCollidableManager();
	EnemyManager& getEnemyManager();
	PauseManager& getPauseManager();
	Player& getPlayer();
	SoundManager& getSoundManager();
	StateManager& getStateManager();
	WaveManager& getWaveManager();
};


#endif // End of '#ifndef GAMEPLAYDIRECTOR_H'