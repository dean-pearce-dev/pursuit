#ifndef ENEMY_H
#define ENEMY_H

#include "GameSprite.h"
#include "EnemyState.h"

class BulletManager;
class CollidableManager;
class Director;
class GameSound;
class SoundManager;
class ReferenceManager;

class Enemy : public GameSprite
{
private:
	BulletManager* m_pBulletManager;

	CollidableManager* m_pCollidableManager;

	const sf::Vector2f* m_pFormationPos;

	GameSound* m_pFireSound;
	GameSound* m_pExplosionSound;

	sf::Vector2f m_positionInFormation;

	sf::Vector2f m_lerpStartPos;

	sf::Vector2f m_offsetFromFormationOrigin;

	EnemyState m_currentState;

	float m_lerpYValue;
	float m_lerpXValue;
	float m_lerpXOffset;
	float m_lerpedXPos;
	float m_playerToLerpStartX;

	float m_fireTimer;

	int m_scoreValue;
	int m_diveSegmentCount;

	bool m_fireIsReady;
	bool m_waveLeft;
	bool m_abovePlayer;
	bool m_formationFirstLerp;

public:
	Enemy();
	virtual ~Enemy();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: update
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Updates the object
	//////////////////////////////////////////////////////////////////////
	virtual void update( float deltaTime );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: init
	/// Parameters: const ReferenceManager& refManager, BulletManager& bulletManager
	/// Returns: void
	/// Purpose: Initialises the object
	//////////////////////////////////////////////////////////////////////
	virtual void init( const ReferenceManager& refManager, BulletManager& bulletManager );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: initPositions
	/// Parameters: const sf::Vector2f& formationPosRef, const sf::Vector2f& positionInFormation, const sf::Vector2f& positionToSpawn
	/// Returns: void
	/// Purpose: Initialise the positions needed for the enemy to remember it's formation pos
	//////////////////////////////////////////////////////////////////////
	virtual void initPositions( const sf::Vector2f& formationPosRef, const sf::Vector2f& positionInFormation, const sf::Vector2f& positionToSpawn );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: flyToFormation
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Makes the enemy fly back to it's formation pos
	//////////////////////////////////////////////////////////////////////
	virtual void flyToFormation( float deltaTime );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: beginReturning
	/// Parameters: none
	/// Returns: void
	/// Purpose: Tells the enemy to start returning to formation
	//////////////////////////////////////////////////////////////////////
	virtual void beginReturning();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getFormationPos
	/// Parameters: none
	/// Returns: sf::Vector2f
	/// Purpose: Returns the enemy's formation pos
	//////////////////////////////////////////////////////////////////////
	sf::Vector2f getFormationPos();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getCurrentState
	/// Parameters: none
	/// Returns: EnemyState
	/// Purpose: returns the enemy's current state
	//////////////////////////////////////////////////////////////////////
	EnemyState getCurrentState();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: setCurrentState
	/// Parameters: EnemyState stateToSet
	/// Returns: void
	/// Purpose: Sets the enemy state
	//////////////////////////////////////////////////////////////////////
	void setCurrentState( EnemyState stateToSet );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: fire
	/// Parameters: none
	/// Returns: void
	/// Purpose: Fires a bullet from the enemy
	//////////////////////////////////////////////////////////////////////
	void fire();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: setToFire
	/// Parameters: none
	/// Returns: void
	/// Purpose: Allows the enemy to fire when the other requirements have been met
	//////////////////////////////////////////////////////////////////////
	void setToFire();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions:  isReadyToFire
	/// Parameters: none
	/// Returns: bool
	/// Purpose: Returns if the enemy is ready to fire
	//////////////////////////////////////////////////////////////////////
	bool isReadyToFire();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: fireRangeCheck
	/// Parameters: none
	/// Returns: bool
	/// Purpose: Checks if the enemy is in range of the player to shoot
	//////////////////////////////////////////////////////////////////////
	bool fireRangeCheck();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: diveBomb
	/// Parameters: float deltaTime
	/// Returns: void
	/// Purpose: Makes the enemy dive bomb at the player
	//////////////////////////////////////////////////////////////////////
	void diveBomb( float deltaTime );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: startDiving
	/// Parameters: none
	/// Returns: void
	/// Purpose: Tells the enemy to start divebombing the player
	//////////////////////////////////////////////////////////////////////
	void startDiving();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: wave
	/// Parameters: float deltaTime, const sf::Vector2f& posToWaveFrom
	/// Returns: const sf::Vector2f&
	/// Purpose: Makes the enemy wave side to side, to be used inside diveBomb()
	//////////////////////////////////////////////////////////////////////
	const sf::Vector2f& wave( float deltaTime, const sf::Vector2f& posToWaveFrom );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: destroy
	/// Parameters: none
	/// Returns: void
	/// Purpose: Sets the enemy to inactive and plays a sound
	//////////////////////////////////////////////////////////////////////
	void destroy();
	
	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: collisionCheck
	/// Parameters: none
	/// Returns: void
	/// Purpose: Checks for collision with other objects
	//////////////////////////////////////////////////////////////////////
	void collisionCheck();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getScoreValue
	/// Parameters: none
	/// Returns: const int
	/// Purpose: Returns the value of points that the enemy is worth
	//////////////////////////////////////////////////////////////////////
	const int getScoreValue() const;

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: setScoreValue
	/// Parameters: const int value
	/// Returns: void
	/// Purpose: Sets the score the enemy is worth
	//////////////////////////////////////////////////////////////////////
	void setScoreValue( const int value );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: reset
	/// Parameters: none
	/// Returns: void
	/// Purpose: Resets the enemy cleanly without the need for reloading the state
	//////////////////////////////////////////////////////////////////////
	void reset();
};

#endif // End of '#ifndef ENEMY_H'
