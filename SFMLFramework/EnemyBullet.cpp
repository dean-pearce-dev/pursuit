#include "EnemyBullet.h"
#include "BarrierManager.h"
#include "Barrier.h"
#include "BarrierSegment.h"
#include "CollidableManager.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Settings.h"

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::update( float deltaTime )
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

	collisionCheck();

	// Check if bullet has gone out of bounds
	if( getPosition().y > k_arenaHeight - ( getTextureDimensions().y / 2 ) )
	{
		disable();
	}
}

void EnemyBullet::collisionCheck()
{
	// Getting references to the player and barrier manager for easy access to position values
	Player& player = getCollidableManager().getPlayer();
	BarrierManager& barrierManager = getCollidableManager().getBarrierManager();

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
						currentSegment.destroy();
						disable();
						return;
					}
				}
			}
		}
	}

	// Player collision
	if( ( getPosition().x + getTextureDimensions().x * 0.5f ) > ( player.getPosition().x - player.getGlobalBounds().width * 0.5f )
		&& ( getPosition().x - getTextureDimensions().x * 0.5f ) < ( player.getPosition().x + player.getGlobalBounds().width * 0.5f )
		&& ( getPosition().y + getTextureDimensions().y * 0.5f ) > ( player.getPosition().y - player.getGlobalBounds().height * 0.5f )
		&& ( getPosition().y - getTextureDimensions().y * 0.5f ) < ( player.getPosition().y + player.getGlobalBounds().height * 0.5f )
		)
	{
		player.takeDamage();
		disable();
		return;
	}
}