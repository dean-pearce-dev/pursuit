#include <random>

#include "Helpers.h"

namespace Math
{
	int randomiseInt( const int min, const int max )
	{
		// Code from https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
		std::random_device dev;
		std::mt19937 rng( dev() );
		std::uniform_int_distribution<std::mt19937::result_type> dist6( min, max );

		return dist6( rng );
	}

	float randomiseFloat( const float min, const float max )
	{
		// Code from above, modified to use float
		std::random_device dev;
		std::mt19937 rng( dev() );
		std::uniform_real_distribution<float> dis( min, max );

		return dis( rng );
	}

	sf::Vector2f lerp( const sf::Vector2f& a, const sf::Vector2f& b, float t )
	{
		return a + t * ( b - a );
	}

	sf::Vector2f quadraticLerp( const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, float t )
	{
		// Using lerp to get new points to base interpolation from
		sf::Vector2f pointAB = lerp( a, b, t );
		sf::Vector2f pointBC = lerp( b, c, t );
		sf::Vector2f lerpedVector = lerp( pointAB, pointBC, t );

		return lerpedVector;
	}

	sf::Vector2f cubicLerp( const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, const sf::Vector2f& d, float t )
	{
		// Using quadraticLerp to get new points to base interpolation from
		sf::Vector2f pointAB_BC = quadraticLerp( a, b, c, t );
		sf::Vector2f pointBC_CD = quadraticLerp( b, c, d, t );
		sf::Vector2f lerpedVector = lerp( pointAB_BC, pointBC_CD, t);

		return lerpedVector;
	}

	float angleToTarget( const sf::Vector2f& currentPos, const sf::Vector2f& targetPos )
	{
		// Code from https://en.sfml-dev.org/forums/index.php?topic=8977.0
		float pi = static_cast<float>( atan( 1 ) * 4 );
		float dx = targetPos.x - currentPos.x;
		float dy = targetPos.y - currentPos.y;

		return ( ( atan2( dy, dx ) ) * 180.0f / pi ) - 90.0f;
	}

	float easeOut( float f )
	{
		float f1 = 1.0f - f;	// f1 is now 1.0-f
		float f2 = f1 * f1;		// f2 is now (1.0-f)*(1.0-f)
		return 1.0f - ( f1 * f2 );
	}

	float easeIn( float f )
	{
		f *= f; // f is now f*f
		return f;
	}

	float easeInOut( float f )
	{
		ASSERT( f >= 0.0f );
		ASSERT( f <= 1.0f );
		return f * f * ( 3.0f - 2.0f * f );
	}
}

namespace Data
{
	// Code from: https://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing
	bool fileExists( const std::string& filename )
	{
		struct stat buf;
		if( stat( filename.c_str(), &buf ) != -1 )
		{
			return true;
		}
		return false;
	}
}