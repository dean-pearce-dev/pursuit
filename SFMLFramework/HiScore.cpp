#include "HiScore.h"
#include "Settings.h"

HiScore::HiScore()
	: m_score		( 0 )
	, m_initials	( k_defaultInitials )
{

}

HiScore::HiScore( const int score, const char initials[] )
	: m_score( score )
	, m_initials( initials )
{
}

HiScore::~HiScore()
{

}

void HiScore::set( const int score, const char initials[] )
{
	m_score = score;
	m_initials = initials;
}

void HiScore::setScore( const int score )
{
	m_score = score;
}

void HiScore::setInitials( const std::string& initials )
{
	m_initials = initials;
}

const int HiScore::getScore() const
{
	return m_score;
}

const std::string HiScore::getInitials() const
{
	return m_initials;
}

void HiScore::reset()
{
	m_score = 0;
	m_initials = k_defaultInitials;
}