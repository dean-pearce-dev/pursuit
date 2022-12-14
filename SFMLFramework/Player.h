#ifndef PLAYER_H
#define PLAYER_H

#include "GameSprite.h"
#include "PlayerState.h"
#include "BulletDir.h"

namespace sf
{
	class RenderWindow;
}

class TextureManager;
class BulletManager;
class CollidableManager;
class InputManager;
class SoundManager;
class ReferenceManager;
class WaveManager;
class GameSound;

class Player : public GameSprite
{
private:
	sf::RenderWindow* m_pWindow;

	TextureManager* m_pTextureManager;

	BulletManager* m_pBulletManager;

	InputManager* m_pInputManager;

	WaveManager* m_pWaveManager;

	PlayerState m_currentState;

	GameSound* m_pFireSound;
	GameSound* m_pLoseLifeSound;
	GameSound* m_pExplosionSound;

	float m_invulnTimer;
	float m_flashTimer;

	float m_tiltAngle;

	int m_lives;
	int m_score;

	bool m_isFiring;
	bool m_isAiming;
	bool m_isVisible;

public:
	Player();
	virtual ~Player();

	void update( float deltaTime );
	void draw();

	void init( const ReferenceManager& refManager );
	
	void move( float deltaTime );
	void fire( const BulletDir direction );
	void aim();

	void flashAnim( float deltaTime );

	void takeDamage();

	PlayerState getState();
	void setState( const PlayerState stateToSet );

	bool isInvuln();

	void addScore( const int scoreToAdd );

	const int getLives() const;
	const int getScore() const;

	int getRemainingBullets();

	void reset();
};

#endif // End of '#ifndef PLAYER_H'
