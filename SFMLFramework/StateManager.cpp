#include "StateManager.h"

StateManager::StateManager()
	: m_currentState ( GameState::Menu )
	, m_currentInGameState( InGameState::Game )
{

};

GameState& StateManager::getState()
{
	return m_currentState;
}

InGameState& StateManager::getInGameState()
{
	return m_currentInGameState;
}

void StateManager::setState( const GameState& stateToSet )
{
	m_currentState = stateToSet;
}

void StateManager::setInGameState( const InGameState& stateToSet )
{
	m_currentInGameState = stateToSet;
}