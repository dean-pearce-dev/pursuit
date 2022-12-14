#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <SFML/System/Vector2.hpp>
#include "WaveState.h"

namespace sf
{
	class RenderWindow;
}

class TextureManager;
class BulletManager;
class WaveManager;
class ReferenceManager;
class Enemy;

class EnemyManager
{
private:
	sf::RenderWindow* m_pWindow;

	TextureManager* m_pTextureManager;

	BulletManager* m_pBulletManager;

	WaveManager* m_pWaveManager;

	Enemy* m_pEnemyArray;

	sf::Vector2f m_formationPos;

	float m_enemyWidth;

	float m_yAtMoveStart;
	float m_totalHorizontalSpace;

	bool m_isMovingLeft;
	
	bool m_isAdvancing;

	bool m_canFire;

	int m_enemyCount;

	int m_activeEnemies;
	int m_inFormationEnemies;
	int m_enemiesReadyToFire;
	int m_enemiesDiving;

	float m_spawnTimer;
	float m_fireTimer;
	float m_diveTimer;

	float m_secondsToNextFire;
	float m_secondsToNextDive;

public:
	EnemyManager();
	~EnemyManager();

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
	/// Parameters: const ReferenceManager& refManager
	/// Returns: void
	/// Purpose: Initialises the object
	//////////////////////////////////////////////////////////////////////
	void init( const ReferenceManager& refManager );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: initEnemies
	/// Parameters: const ReferenceManager& refManager
	/// Returns: void
	/// Purpose: Intialises the enemies that will be used
	//////////////////////////////////////////////////////////////////////
	void initEnemies( const ReferenceManager& refManager );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getEnemyCount
	/// Parameters: none
	/// Returns: int
	/// Purpose: Returns the total enemy count
	//////////////////////////////////////////////////////////////////////
	int getEnemyCount();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getActiveEnemyCount
	/// Parameters: none
	/// Returns: int
	/// Purpose: Returns the total active enemies
	//////////////////////////////////////////////////////////////////////
	int getActiveEnemyCount();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getEnemyByIndex
	/// Parameters: const int index
	/// Returns: Enemy&
	/// Purpose: Returns an enemy based on the index num
	//////////////////////////////////////////////////////////////////////
	Enemy& getEnemyByIndex( const int index );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: move
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Move the enemies
	//////////////////////////////////////////////////////////////////////
	void move( float deltaTime );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: attackCheck
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Checks if the enemies can attack, and if so, determines what attack to use
	//////////////////////////////////////////////////////////////////////
	void attackCheck( float deltaTime );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: setupWave
	/// Parameters: const int rows, const int enemiesPerRow
	/// Returns: void
	/// Purpose: Setup the wave
	//////////////////////////////////////////////////////////////////////
	void setupWave( const int rows, const int enemiesPerRow );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: beginWave
	/// Parameters: none
	/// Returns: void
	/// Purpose: Begins the wave and starts moving the enemies
	//////////////////////////////////////////////////////////////////////
	void beginWave();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: activeEnemyCount
	/// Parameters: none
	/// Returns: void
	/// Purpose: Makes checks for how many enemies are active
	//////////////////////////////////////////////////////////////////////
	void activeEnemyCount();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: reset
	/// Parameters: none
	/// Returns: void
	/// Purpose: Resets the object
	//////////////////////////////////////////////////////////////////////
	void reset();
};

#endif // End of '#ifndef ENEMYMANAGER_H'