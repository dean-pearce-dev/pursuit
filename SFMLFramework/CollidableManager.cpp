#include "CollidableManager.h"

CollidableManager::CollidableManager()
	:	m_pPlayer			( nullptr )
	,	m_pEnemyManager		( nullptr )
	,	m_pBarrierManager	( nullptr )
{

}

CollidableManager::~CollidableManager()
{

}

void CollidableManager::init( Player& player, EnemyManager& enemyManager, BarrierManager& barrierManager )
{
	m_pPlayer = &player;
	m_pEnemyManager = &enemyManager;
	m_pBarrierManager = &barrierManager;
}

Player& CollidableManager::getPlayer()
{
	return *m_pPlayer;
}

EnemyManager& CollidableManager::getEnemyManager()
{
	return *m_pEnemyManager;
}

BarrierManager& CollidableManager::getBarrierManager()
{
	return *m_pBarrierManager;
}