#ifndef HISCOREMANAGER_H
#define HISCOREMANAGER_H

#include <vector>

class HiScore;
class ReferenceManager;

class HiScoreManager
{
private:
	//HiScore* m_pHiScoreArray;
	std::vector<HiScore> m_hiScoreArray;

	int m_lowestScore;

public:
	HiScoreManager();
	~HiScoreManager();

	void init();

	void draw();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: readScoreData
	/// Parameters: none
	/// Returns: void
	/// Purpose: Reads the score data and holds it in a vector of HiScore objects
	//////////////////////////////////////////////////////////////////////
	void readScoreData();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: saveScoreData
	/// Parameters: none
	/// Returns: void
	/// Purpose: Saves the HiScore data currently held
	//////////////////////////////////////////////////////////////////////
	void saveScoreData();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: sortByScore
	/// Parameters: none
	/// Returns: void
	/// Purpose: Sorts the HiScore objects by highest score to lowest score
	//////////////////////////////////////////////////////////////////////
	void sortByScore();

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions:addNewHiScore 
	/// Parameters: const std::string& initials, int score
	/// Returns: void
	/// Purpose: Replaces the lowest score in the vector with the new high score
	//////////////////////////////////////////////////////////////////////
	void addNewHiScore( const std::string& initials, int score );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getLowestScore
	/// Parameters: none
	/// Returns: const int
	/// Purpose: Returns the lowest score in the vector
	//////////////////////////////////////////////////////////////////////
	const int getLowestScore() const;

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: getHiScoreByIndex
	/// Parameters: const int i
	/// Returns: const HiScore&
	/// Purpose: Returns HiScore object by index
	//////////////////////////////////////////////////////////////////////
	const HiScore& getHiScoreByIndex( const int i );

	//////////////////////////////////////////////////////////////////////
	/// Function/Functions: reset
	/// Parameters: none
	/// Returns: void
	/// Purpose: Resets the object
	//////////////////////////////////////////////////////////////////////
	void reset();
};

#endif // End of '#ifndef HISCOREMANAGER_H'