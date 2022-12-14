#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "BulletDir.h"
#include "EnemyManager.h"

namespace sf
{
	class RenderWindow;
}

class Bullet;
class CollidableManager;
class ReferenceManager;
class TextureManager;

class BulletManager
{
private:
	sf::RenderWindow* m_pWindow;

	std::vector<Bullet*> m_pBulletArray;

	CollidableManager* m_pCollidableManager;

	TextureManager* m_pTextureManager;

	int m_pooledBulletCount;

	int m_firedBullets;
	int m_maxFiredBullets;

	float m_reloadTimer;
	float m_reloadDelay;

public:
	BulletManager();
	~BulletManager();

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
	/// Parameters: Director& director
	/// Returns: void
	/// Purpose: Initialises the object
	//////////////////////////////////////////////////////////////////////
	void init( const ReferenceManager& refManager );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: initPlayerBullets, initEnemyBullets
	/// Parameters: none
	/// Returns: void
	/// Purpose: Initialises bullets for the specified object
	//////////////////////////////////////////////////////////////////////
	void initPlayerBullets();
	void initEnemyBullets();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: fire
	/// Parameters: const sf::Vector2f& currentPos, BulletDir bulletDir
	/// Returns: void
	/// Purpose: Fires a bullet in the given direction, from the given pos
	//////////////////////////////////////////////////////////////////////
	void fire( const sf::Vector2f& currentPos, BulletDir bulletDir );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: reloadBullets
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Gradually reloads bullets to the bullet manager
	//////////////////////////////////////////////////////////////////////
	void reloadBullets( float deltaTime );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getFiredBullets
	/// Parameters: none
	/// Returns: const int
	/// Purpose: Returns the number of bullets currently fired
	//////////////////////////////////////////////////////////////////////
	const int getFiredBullets();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: canFire
	/// Parameters: none
	/// Returns: bool
	/// Purpose: Returns whether the bullet manager can fire or not
	//////////////////////////////////////////////////////////////////////
	bool canFire();
	
	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: reset
	/// Parameters: none
	/// Returns: void
	/// Purpose: Resets the object
	//////////////////////////////////////////////////////////////////////
	void reset();
};

#endif // End of '#ifndef BULLETMANAGER_H'
