#ifndef BULLET_H
#define BULLET_H

#include "GameSprite.h"
#include "BulletDir.h"

class CollidableManager;

class Bullet : public GameSprite
{
private:
	CollidableManager* m_pCollidableManager;

	BulletDir m_currentDir;

	float m_speed;

	bool m_isActive;

public:
	Bullet();
	virtual ~Bullet();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: update
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Updates the object
	//////////////////////////////////////////////////////////////////////
	virtual void update( float deltaTime );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: init
	/// Parameters: const sf::Texture& textureToSet
	/// Returns: void
	/// Purpose: Initialises the object and sets the texture based on parameter
	//////////////////////////////////////////////////////////////////////
	void init( const sf::Texture& textureToSet );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: isActive
	/// Parameters: none
	/// Returns: bool
	/// Purpose: Returns whether the object is active or inactive
	//////////////////////////////////////////////////////////////////////
	bool isActive();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: setActive
	/// Parameters: bool setActive
	/// Returns: void
	/// Purpose: Sets the active state of the object via parameter
	//////////////////////////////////////////////////////////////////////
	void setActive( bool setActive );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: collisionCheck
	/// Parameters: none
	/// Returns: void
	/// Purpose: Checks for collision with other objects
	//////////////////////////////////////////////////////////////////////
	virtual void collisionCheck();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getSpeed
	/// Parameters: none
	/// Returns: float
	/// Purpose: Returns the speed of the object
	//////////////////////////////////////////////////////////////////////
	float getSpeed();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getDir
	/// Parameters: none
	/// Returns: const BulletDir
	/// Purpose: Returns the direction the bullet is travelling
	//////////////////////////////////////////////////////////////////////
	const BulletDir getDir() const;

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: setDir
	/// Parameters: BulletDir direction
	/// Returns: void
	/// Purpose: Sets the direction the bullet should travel in
	//////////////////////////////////////////////////////////////////////
	void setDir( BulletDir direction );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: setCollidableManager
	/// Parameters: CollidableManager& collidableManager
	/// Returns: void
	/// Purpose: Sets a reference to the collidableManager for the Bullet 
	///			 to use for collision checking
	//////////////////////////////////////////////////////////////////////
	void setCollidableManager( CollidableManager& collidableManager );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getCollidableManager
	/// Parameters: none
	/// Returns: CollidableManager&
	/// Purpose: Returns a reference to the collidable manager
	//////////////////////////////////////////////////////////////////////
	CollidableManager& getCollidableManager();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: disable
	/// Parameters: none
	/// Returns: void
	/// Purpose: Disables the bullet
	//////////////////////////////////////////////////////////////////////
	void disable();
};

#endif // End of '#ifndef BULLET_H'