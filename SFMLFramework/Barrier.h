#ifndef BARRIER_H
#define BARRIER_H

namespace sf
{
	class RenderWindow;
}

class BarrierSegment;
class ReferenceManager;

class Barrier
{
private:
	BarrierSegment* m_pSegmentArray;

	sf::Vector2f m_position;

	bool m_isActive;

public:
	Barrier();
	~Barrier();

	void update( float deltaTime );
	void draw();

	void init( const ReferenceManager& refManager );

	void reset();
	void disable();

	bool isActive();

	bool segmentCheck();

	BarrierSegment& getSegmentByIndex( const int index );

	const sf::Vector2f& getPosition();
	void setPosition( const sf::Vector2f& position );
};

#endif // End of '#ifndef BARRIER_H'