#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "Bullet.h"

class PlayerBullet : public Bullet
{
private:

public:
	PlayerBullet();
	virtual ~PlayerBullet();

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
	/// Purpose: Checks for collision with the enemy objects
	//////////////////////////////////////////////////////////////////////
	virtual void collisionCheck() override;
};

#endif // End of '#ifndef PLAYERBULLET_H'