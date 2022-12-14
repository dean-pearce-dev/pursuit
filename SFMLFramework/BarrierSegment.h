#ifndef BARRIERSEGMENT_H
#define BARRIERSEGMENT_H

#include "GameSprite.h"

namespace sf
{
	class RenderWindow;
	class SoundBuffer;
}

class ReferenceManager;
class GameSound;

class BarrierSegment : public GameSprite
{
private:
	sf::RenderWindow* m_pWindow;

	GameSound* m_pExplosionSound;

	bool m_isActive;

public:
	BarrierSegment();
	~BarrierSegment();

	void update( float deltaTime );
	void draw();

	void init( const ReferenceManager& refManager, const int segmentNum );

	void enable();
	void disable();
	void destroy();

	bool isActive();

};

#endif // End of '#ifndef BARRIERSEGMENT_H'