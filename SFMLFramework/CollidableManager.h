#ifndef	COLLIDABLEMANAGER_H
#define COLLIDABLEMANAGER_H

class BarrierManager;
class EnemyManager;
class Player;

class CollidableManager
{
private:
	Player* m_pPlayer;

	EnemyManager* m_pEnemyManager;

	BarrierManager* m_pBarrierManager;

public:
	CollidableManager();
	~CollidableManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: init
	/// Parameters: Director& director
	/// Returns: void
	/// Purpose: Initialises the object
	//////////////////////////////////////////////////////////////////////
	void init( Player& player, EnemyManager& enemyManager, BarrierManager& barrierManager );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getPlayer
	/// Parameters: none
	/// Returns: Player&
	/// Purpose: Returns a reference to the player
	//////////////////////////////////////////////////////////////////////
	Player& getPlayer();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getEnemyManager
	/// Parameters: none
	/// Returns: EnemyManager&
	/// Purpose: Returns a reference to the enemy manager
	//////////////////////////////////////////////////////////////////////
	EnemyManager& getEnemyManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getBarrierManager
	/// Parameters: none
	/// Returns: BarrierManager&
	/// Purpose: Returns a reference to the barrier manager
	//////////////////////////////////////////////////////////////////////
	BarrierManager& getBarrierManager();
};

#endif // End of '#ifndef COLLIDABLEMANAGER_H'