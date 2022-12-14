#include <fstream>
#include <algorithm>

#include "HiScoreManager.h"
#include "HiScore.h"
#include "ReferenceManager.h"
#include "Helpers.h"
#include "Settings.h"

HiScoreManager::HiScoreManager()
	: m_lowestScore ( 0 )
	, m_hiScoreArray ( k_savedHighScoresNum )
{

}

HiScoreManager::~HiScoreManager()
{

}

void HiScoreManager::init()
{
	if( Data::fileExists( "data/scores.txt" ) )
	{
		readScoreData();
	}
	else
	{
		saveScoreData();
	}
}

void HiScoreManager::draw()
{

}

void HiScoreManager::readScoreData()
{
	std::ifstream scoreFile;
	scoreFile.open( "data/scores.txt" );

	if( scoreFile.is_open() )
	{
		for( int i = 0; i < k_savedHighScoresNum; i++ )
		{
			// Adding 1 to k_scoreInitialsLength because of the null terminate char
			char initials[k_scoreInitialsLength + 1];
			int score = 0;

			scoreFile >> initials;
			scoreFile >> score;
			m_hiScoreArray[i].set( score, initials );
		}
	}

	scoreFile.close();

	sortByScore();
}

void HiScoreManager::saveScoreData()
{
	std::ofstream scoreFile;
	scoreFile.open( "data/scores.txt" );

	if( scoreFile.is_open() )
	{
		for( int i = 0; i < k_savedHighScoresNum; i++ )
		{
			scoreFile << m_hiScoreArray[i].getInitials();
			scoreFile << "\n";
			scoreFile << m_hiScoreArray[i].getScore();
			scoreFile << "\n";
		}
	}
	else
	{

	}

	scoreFile.close();
}

void HiScoreManager::sortByScore()
{
	std::sort( m_hiScoreArray.begin(), m_hiScoreArray.end(), std::greater<>() );
	m_lowestScore = m_hiScoreArray[k_savedHighScoresNum - 1].getScore();
}

void HiScoreManager::addNewHiScore( const std::string& initials, int score )
{
	m_hiScoreArray[k_savedHighScoresNum - 1].setInitials( initials );
	m_hiScoreArray[k_savedHighScoresNum - 1].setScore( score );
	sortByScore();
	saveScoreData();
}

const int HiScoreManager::getLowestScore() const
{
	return m_lowestScore;
}

const HiScore& HiScoreManager::getHiScoreByIndex( const int i )
{
	return m_hiScoreArray[i];
}

void HiScoreManager::reset()
{
	for( int i = 0; i < k_savedHighScoresNum; i++ )
	{
		m_hiScoreArray[i].reset();
	}
}