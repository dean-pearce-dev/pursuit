#ifndef	TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "GameState.h"

namespace sf
{
	class Texture;
}

class TextureManager
{
private:
	sf::Texture* m_pPlayerShip;

	sf::Texture* m_pEnemyShip;

	sf::Texture* m_pPlayerBullet;

	sf::Texture* m_pEnemyBullet;

	sf::Texture* m_pBarrier;

	sf::Texture* m_pBackground;

	sf::Texture* m_pAmmoBarSegment;

	sf::Texture* m_pHealthBarSegment;

public:
	TextureManager();

	~TextureManager();

	bool load( const char* fileName, sf::Texture& textureToSet );

	void loadTextures( GameState stateToLoad );
	void unloadTextures( GameState stateToUnload);

	void loadPersistentTextures();

	void unloadAllTextures();

	const sf::Texture& getPlayerShip() const;

	const sf::Texture& getEnemyShip() const;

	const sf::Texture& getPlayerBullet() const;

	const sf::Texture& getEnemyBullet() const;

	const sf::Texture& getBarrier() const;

	const sf::Texture& getBackground() const;

	const sf::Texture& getAmmoBarSegment() const;

	const sf::Texture& getHealthBarSegment() const;
};

#endif // End of '#ifndef TEXTUREMANAGER_H'