#include "PlayerBullet.h"
#include "Barrier.h"
#include "BarrierManager.h"
#include "BarrierSegment.h"
#include "BulletDir.h"
#include "CollidableManager.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Settings.h"

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::update( float deltaTime )
{
	// Moving using a switch based on current direction
	switch( getDir() )
	{
		case BulletDir::Up:
		{
			move( 0.0f, -( getSpeed() * deltaTime ) );
		}
		break;
		case BulletDir::UpLeft:
		{
			move( ( -getSpeed() / 2 ) * deltaTime, ( -getSpeed() / 2 ) * deltaTime );
		}
		break;
		case BulletDir::UpRight:
		{
			move( ( getSpeed() / 2 ) * deltaTime, ( -getSpeed() / 2 ) * deltaTime );

		}
		break;
		case BulletDir::Down:
		{
			move( 0.0f, ( getSpeed() * deltaTime ) );

		}
		break;
	}



	// Check for collision with enemy ships
	collisionCheck();

	// Check if bullet has gone out of bounds
	if( getPosition().x < getTextureDimensions().x / 2 || getPosition().x > k_arenaWidth + getTextureDimensions().x / 2 || getPosition().y < getTextureDimensions().y / 2 )
	{
		disable();
	}
}

void PlayerBullet::collisionCheck()
{
	// Getting references to the enemy and barrier manager for easy access to position values, and the player for incrementing score
	EnemyManager& enemyManager = getCollidableManager().getEnemyManager();
	BarrierManager& barrierManager = getCollidableManager().getBarrierManager();
	Player& player = getCollidableManager().getPlayer();

	for( int i = 0; i < enemyManager.getEnemyCount(); i++ )
	{
		// Get reference to the enemy that needs to be checked
		Enemy& currentEnemy = enemyManager.getEnemyByIndex( i );

		// Check whether enemy is active to decide whether to skip collision check
		if( currentEnemy.getCurrentState() != EnemyState::Inactive )
		{
			// Enemy collision
			if( ( getPosition().x + getTextureDimensions().x * 0.5f ) > ( currentEnemy.getPosition().x - currentEnemy.getGlobalBounds().width * 0.5f )
				&& ( getPosition().x - getTextureDimensions().x * 0.5f ) < ( currentEnemy.getPosition().x + currentEnemy.getGlobalBounds().width * 0.5f )
				&& ( getPosition().y + getTextureDimensions().y * 0.5f ) > ( currentEnemy.getPosition().y - currentEnemy.getGlobalBounds().height * 0.5f )
				&& ( getPosition().y - getTextureDimensions().y * 0.5f ) < ( currentEnemy.getPosition().y + currentEnemy.getGlobalBounds().height * 0.5f )
				)
			{
				currentEnemy.destroy();
				disable();
				player.addScore( currentEnemy.getScoreValue() );
				return;
			}
		}
	}

	for( int i = 0; i < barrierManager.getBarrierAmount(); i++ )
	{
		for( int i = 0; i < barrierManager.getBarrierAmount(); i++ )
		{
			Barrier& currentBarrier = barrierManager.getBarrierByIndex( i );
			if( currentBarrier.isActive() )
			{
				for( int j = 0; j < k_barrierHealth; j++ )
				{
					BarrierSegment& currentSegment = currentBarrier.getSegmentByIndex( j );
					if( currentSegment.isActive() )
					{
						// Barrier collision
						if( ( getPosition().x + getTextureDimensions().x * 0.5f ) > ( currentSegment.getPosition().x - currentSegment.getGlobalBounds().width * 0.5f )
							&& ( getPosition().x - getTextureDimensions().x * 0.5f ) < ( currentSegment.getPosition().x + currentSegment.getGlobalBounds().width * 0.5f )
							&& ( getPosition().y + getTextureDimensions().y * 0.5f ) > ( currentSegment.getPosition().y - currentSegment.getGlobalBounds().height * 0.5f )
							&& ( getPosition().y - getTextureDimensions().y * 0.5f ) < ( currentSegment.getPosition().y + currentSegment.getGlobalBounds().height * 0.5f ) )
						{
							disable();
							return;
						}
					}
				}
			}
		}
	}
}