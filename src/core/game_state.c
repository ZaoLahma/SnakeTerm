#include "../../inc/game_state.h"

static GameState currState;

void initGameState(void)
{
	currState = GAME_SYS_INIT;
}

void getGameState(GameState* state)
{
	*state = currState;
}

void setGameState(const GameState state)
{
	currState = state;
}
