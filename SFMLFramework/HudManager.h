#ifndef HUDMANAGER_H
#define HUDMANAGER_H

namespace sf
{
	class RenderWindow;
}

class GameSprite;
class GameText;
class Player;
class ReferenceManager;

class HudManager
{
private:
	sf::RenderWindow* m_pWindow;

	GameSprite* m_pAmmoBarArray;
	GameSprite* m_pLivesArray;

	GameText* m_pScoreText;

	Player* m_pPlayer;

public:
	HudManager();
	~HudManager();

	void update();
	void draw();

	void init( ReferenceManager& refManager );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: ammoBarCheck
	/// Parameters: none
	/// Returns: void
	/// Purpose: Sets the ammo bar color depending on whether the bullet is fired or not
	//////////////////////////////////////////////////////////////////////
	void ammoBarCheck();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: livesCheck
	/// Parameters: none
	/// Returns: void
	/// Purpose: Sets the lives bar color depending on how many lives the player has
	//////////////////////////////////////////////////////////////////////
	void livesCheck();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: scoreCheck
	/// Parameters: none
	/// Returns: void
	/// Purpose: Sets the score string to contain the player's current score
	//////////////////////////////////////////////////////////////////////
	void scoreCheck();
};

#endif // End of '#ifndef HUDMANAGER_H'