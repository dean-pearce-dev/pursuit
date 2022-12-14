#ifndef CREDITS_H
#define CREDITS_H

namespace sf
{
	class RenderWindow;
}

class ReferenceManager;
class Director;
class GameText;

class Credits
{
private:
	sf::RenderWindow* m_pWindow;

	std::vector<GameText*> m_gameTextArray;

	GameText* m_pDevelopedText;
	GameText* m_pNameText;
	GameText* m_pMusicByText;
	GameText* m_pMenuMusicText;
	GameText* m_pGameMusicText;
	GameText* m_pEffectsFromText;
	GameText* m_pZapsplatText;
	GameText* m_pFontFromText;
	GameText* m_pFontText;

	float m_scrollSpeed;


public:
	Credits();
	~Credits();

	void update( float deltaTime );
	void draw();

	void init( Director& director );

	void reinitPos();

	bool creditsFinished();
};

#endif // End of '#ifndef CREDITS_H'