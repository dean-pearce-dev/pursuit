#ifndef HISCORE_H
#define HISCORE_H

#include <string>

class HiScore
{
private:
	int m_score;
	std::string m_initials;

public:
	HiScore();
	HiScore( const int score, const char initials[] );
	~HiScore();

	void set( const int score, const char initials[] );
	void setScore( const int score );
	void setInitials( const std::string& initials );

	const int getScore() const;
	const std::string getInitials() const;

	void reset();

	bool operator>( const HiScore& other )
	{
		bool isGreaterThan = false;
		if( m_score > other.getScore() )
		{
			isGreaterThan = true;
		}

		return isGreaterThan;
	}

	bool operator<( const HiScore& other )
	{
		bool isLessThan = false;
		if( m_score < other.getScore() )
		{
			isLessThan = true;
		}

		return isLessThan;
	}

	bool operator>=( const HiScore& other )
	{
		bool isEqualOrGreater = false;
		if( m_score >= other.getScore() )
		{
			isEqualOrGreater = true;
		}

		return isEqualOrGreater;
	}

	bool operator<=( const HiScore& other )
	{
		bool isEqualOrLess = false;
		if( m_score <= other.getScore() )
		{
			isEqualOrLess = true;
		}

		return isEqualOrLess;
	}

	bool operator==( const HiScore& other )
	{
		bool isEqualTo = false;
		if( m_score == other.getScore() )
		{
			isEqualTo = true;
		}

		return isEqualTo;
	}
};

#endif // End of '#ifndef HISCORE_H'