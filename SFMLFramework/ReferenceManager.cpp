#include "ReferenceManager.h"
#include "Director.h"
#include "GameplayDirector.h"

ReferenceManager::ReferenceManager()
	: m_pBackgroundManager	( nullptr )
	, m_pBarrierManager		( nullptr )
	, m_pCollidableManager	( nullptr )
	, m_pDirector			( nullptr )
	, m_pEnemyManager		( nullptr )
	, m_pFontManager		( nullptr )
	, m_pGameplayDirector	( nullptr )
	, m_pInputManager		( nullptr )
	, m_pMainMenuManager	( nullptr )
	, m_pPauseManager		( nullptr )
	, m_pPlayer				( nullptr )
	, m_pSoundManager		( nullptr )
	, m_pStateManager		( nullptr )
	, m_pTextureManager		( nullptr )
	, m_pWaveManager		( nullptr )
	, m_pWindow				( nullptr )
{

}

ReferenceManager::~ReferenceManager()
{

}

void ReferenceManager::initDirectorRefs( Director& director )
{
	m_pDirector = &director;
	m_pWindow = &director.getWindowHandle();
	m_pBackgroundManager = &director.getBackgroundManager();
	m_pFontManager = &director.getFontManager();
	m_pHiScoreManager = &director.getHiScoreManager();
	m_pInputManager = &director.getInputManager();
	m_pMainMenuManager = &director.getMainMenuManager();
	m_pSoundManager = &director.getSoundManager();
	m_pStateManager = &director.getStateManager();
	m_pTextureManager = &director.getTextureManager();
}

void ReferenceManager::initGameplayRefs( GameplayDirector& gameplayDirector )
{
	m_pGameplayDirector = &gameplayDirector;

	m_pBackgroundManager = &m_pGameplayDirector->getBackgroundManager();
	m_pBarrierManager = &m_pGameplayDirector->getBarrierManager();
	m_pCollidableManager = &m_pGameplayDirector->getCollidableManager();
	m_pEnemyManager = &m_pGameplayDirector->getEnemyManager();
	m_pPauseManager = &m_pGameplayDirector->getPauseManager();
	m_pPlayer = &m_pGameplayDirector->getPlayer();
	m_pWaveManager = &m_pGameplayDirector->getWaveManager();
}

BackgroundManager& ReferenceManager::getBackgroundManager() const
{
	return *m_pBackgroundManager;
}

BarrierManager& ReferenceManager::getBarrierManager() const
{
	return *m_pBarrierManager;
}

CollidableManager& ReferenceManager::getCollidableManager() const
{
	return *m_pCollidableManager;
}

Director& ReferenceManager::getDirector() const
{
	return *m_pDirector;
}

EnemyManager& ReferenceManager::getEnemyManager() const
{
	return *m_pEnemyManager;
}

FontManager& ReferenceManager::getFontManager() const
{
	return *m_pFontManager;
}

GameplayDirector& ReferenceManager::getGameplayDirector() const
{
	return *m_pGameplayDirector;
}

HiScoreManager& ReferenceManager::getHiScoreManager() const
{
	return *m_pHiScoreManager;
}

InputManager& ReferenceManager::getInputManager() const
{
	return *m_pInputManager;
}

MainMenuManager& ReferenceManager::getMainMenuManager() const
{
	return *m_pMainMenuManager;
}

PauseManager& ReferenceManager::getPauseManager() const
{
	return *m_pPauseManager;
}

Player& ReferenceManager::getPlayer() const
{
	return *m_pPlayer;
}

SoundManager& ReferenceManager::getSoundManager() const
{
	return *m_pSoundManager;
}

StateManager& ReferenceManager::getStateManager() const
{
	return *m_pStateManager;
}

TextureManager& ReferenceManager::getTextureManager() const
{
	return *m_pTextureManager;
}

WaveManager& ReferenceManager::getWaveManager() const
{
	return *m_pWaveManager;
}

sf::RenderWindow& ReferenceManager::getWindowHandle() const
{
	return *m_pWindow;
}