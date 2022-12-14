#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "Bullet.h"

class EnemyBullet : public Bullet
{
private:

public:
	EnemyBullet();
	virtual ~EnemyBullet();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: update
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Updates the object
	//////////////////////////////////////////////////////////////////////
	virtual void update( float deltaTime ) override;

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: collisionCheck
	/// Parameters: none
	/// Returns: void
	/// Purpose: Checks for collision with the player or barriers
	//////////////////////////////////////////////////////////////////////
	virtual void collisionCheck() override;
};

#endif // End of '#ifndef ENEMYBULLET_H'