#ifndef REFERENCEMANAGER_H
#define REFERENCEMANAGER_H

namespace sf
{
	class RenderWindow;
}

class BackgroundManager;
class BarrierManager;
class CollidableManager;
class Director;
class EnemyManager;
class FontManager;
class GameplayDirector;
class HiScoreManager;
class InputManager;
class MainMenuManager;
class PauseManager;
class Player;
class SoundManager;
class StateManager;
class TextureManager;
class WaveManager;

class ReferenceManager
{
private:
	BackgroundManager* m_pBackgroundManager;
	BarrierManager* m_pBarrierManager;
	CollidableManager* m_pCollidableManager;
	Director* m_pDirector;
	EnemyManager* m_pEnemyManager;
	FontManager* m_pFontManager;
	GameplayDirector* m_pGameplayDirector;
	HiScoreManager* m_pHiScoreManager;
	InputManager* m_pInputManager;
	MainMenuManager* m_pMainMenuManager;
	PauseManager* m_pPauseManager;
	Player* m_pPlayer;
	SoundManager* m_pSoundManager;
	StateManager* m_pStateManager;
	TextureManager* m_pTextureManager;
	WaveManager* m_pWaveManager;
	sf::RenderWindow* m_pWindow;

public:
	ReferenceManager();
	~ReferenceManager();

	void initDirectorRefs( Director& director );
	void initGameplayRefs( GameplayDirector& gameplayDirector );

	BackgroundManager& getBackgroundManager() const;
	BarrierManager& getBarrierManager() const;
	CollidableManager& getCollidableManager() const;
	Director& getDirector() const;
	EnemyManager& getEnemyManager() const;
	FontManager& getFontManager() const;
	GameplayDirector& getGameplayDirector() const;
	HiScoreManager& getHiScoreManager() const;
	InputManager& getInputManager() const;
	MainMenuManager& getMainMenuManager() const;
	PauseManager& getPauseManager() const;
	Player& getPlayer() const;
	SoundManager& getSoundManager() const;
	StateManager& getStateManager() const;
	TextureManager& getTextureManager() const;
	WaveManager& getWaveManager() const;
	sf::RenderWindow& getWindowHandle() const;
};

#endif // End of '#ifndef REFERENCEMANAGER_H'