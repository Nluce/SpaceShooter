#pragma once

class StateManager
{
public:

	StateManager();
	~StateManager();
	enum GameStates
	{
		eMAIN_MENU,
		eGAMEPLAY,
		eEND,
		eNEWLIFE,
		eGAMEOVER
	};
	void SetState(GameStates gameState);
	GameStates GetState();

private:
	GameStates gameState;
};

