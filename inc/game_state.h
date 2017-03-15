#ifndef HEADER_GAME_STATE
#define HEADER_GAME_STATE

typedef enum GameState_
{
	GAME_SYS_INIT,
	GAME_SYS_SETUP_COMPLETE,
	GAME_CONFIGURE_RUNNING,
	GAME_SNAKE_INIT,
	GAME_SNAKE_RUNNING,
	GAME_NO_OF_STATES
} GameState;

void initGameState(void);
void getGameState(GameState* state);
void setGameState(const GameState state);

#endif
