#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include "WaveState.h"

class ReferenceManager;
class EnemyManager;
class Player;

class WaveManager
{
private:
	EnemyManager* m_pEnemyManager;

	Player* m_pPlayer;

	WaveState m_currentState;

	float m_waveTimer;

	int m_currentWave;

public:
	WaveManager();
	~WaveManager();

	void update( float deltaTime );

	void init( const ReferenceManager& refManager );

	void spawnWave();

	void initState( WaveState stateToInit );
	void uninitState();

	void changeState( WaveState stateToInit );

	WaveState getState();
	void setState( WaveState stateToSet );

	bool isWaveActive();
	bool isLevelComplete();

	void reset();
};

#endif // End of '#ifndef WAVEMANAGER_H'