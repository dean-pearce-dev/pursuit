#ifndef HELPERS_H
#define HELPERS_H

#include <SFML/System/Vector2.hpp>
#include <string>
#include <cassert>

#ifdef _DEBUG
#define ASSERT(a) assert(a)
#else
#define ASSERT(a) 
#endif

//////////////////////////////////////////////////////////////////////
/// Function/Functions: safeDelete
/// Parameters: T * &p
/// Returns: void
/// Purpose: Safely deletes a pointer for freeing up memory
//////////////////////////////////////////////////////////////////////
template<typename T>
void safeDelete( T * &p )
{
	if( p )
	{
		delete p;
		p = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////
/// Function/Functions: safeArrayDelete
/// Parameters: T * &p
/// Returns: void
/// Purpose: Safely deletes a pointer array for freeing up memory
//////////////////////////////////////////////////////////////////////
template<typename T>
void safeDeleteArray( T*& p )
{
	if( p )
	{
		delete[] p;
		p = nullptr;
	}
}

namespace Math
{
	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: randomiseInt
	/// Parameters: const int min, const int max
	/// Returns: int
	/// Purpose: Randomises an int between the values passed in as paramaters and returns it
	//////////////////////////////////////////////////////////////////////
	int randomiseInt( const int min, const int max );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: randomiseFloat
	/// Parameters: const float min, const float max
	/// Returns: float
	/// Purpose: Randomises an float between the values passed in as paramaters and returns it
	//////////////////////////////////////////////////////////////////////
	float randomiseFloat( const float min, const float max );

	// lerp() function was learned during lectures
	// quadraticLerp() and cubicLerp() were used in a previous Unity module and I have adapted them for C++
	// Original quadraticLerp() and cubicLerp() functions were found here https://www.youtube.com/watch?v=7j_BNf9s0jM

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: lerp
	/// Parameters: const sf::Vector2f& a, const sf::Vector2f& b, float t
	/// Returns: sf::Vector2f
	/// Purpose: Returns a position interpolated between two points determined by the float
	//////////////////////////////////////////////////////////////////////
	sf::Vector2f lerp( const sf::Vector2f& a, const sf::Vector2f& b, float t );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: quadraticLerp
	/// Parameters: const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, float t
	/// Returns: sf::Vector2f
	/// Purpose: Returns a position interpolated between three points determined by the float
	//////////////////////////////////////////////////////////////////////
	sf::Vector2f quadraticLerp( const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, float t );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: cubicLerp
	/// Parameters: const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, const sf::Vector2f& d, float t
	/// Returns: sf::Vector2f
	/// Purpose: Returns a position interpolated between four points determined by the float
	//////////////////////////////////////////////////////////////////////
	sf::Vector2f cubicLerp( const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, const sf::Vector2f& d, float t );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: angleToTarget
	/// Parameters: const sf::Vector2f& currentPos, const sf::Vector2f& targetPos
	/// Returns: float
	/// Purpose: Returns the angle needed for rotation to look at a target position
	//////////////////////////////////////////////////////////////////////
	float angleToTarget( const sf::Vector2f& currentPos, const sf::Vector2f& targetPos );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: easeOut(), easeIn(), easeInOut()
	/// Parameters: float f
	/// Returns: float
	/// Purpose: Functions for altering the speed of interpolation
	//////////////////////////////////////////////////////////////////////
	float easeOut( float f );
	float easeIn( float f );
	float easeInOut( float f );
}

namespace Data
{
	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: fileExists
	/// Parameters: const std::string& filename
	/// Returns: bool
	/// Purpose: Returns a bool based on whether a specified file exists
	//////////////////////////////////////////////////////////////////////
	bool fileExists( const std::string& filename );
}

#endif // End of '#ifndef HELPERS_H'
