#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "GameState.h"
#include "InGameState.h"

class StateManager
{
private:
	GameState m_currentState;
	InGameState m_currentInGameState;
	
public:
	StateManager();

	GameState& getState();
	InGameState& getInGameState();

	void setState( const GameState& stateToSet );
	void setInGameState( const InGameState& stateToSet );
};

#endif // End of '#ifndef STATEMANAGER_H'
