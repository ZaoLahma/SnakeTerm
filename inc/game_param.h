#ifndef HEADER_GAME_PARAM
#define HEADER_GAME_PARAM

typedef enum GameParamId_
{
	GAME_PARAM_HIGH_SCORE,
	GAME_PARAM_NO_OF_PARAMS
} GameParamId;

void initGameParam(void);
unsigned int setGameParam(GameParamId paramId, unsigned int value);
unsigned int getGameParam(GameParamId paramId, unsigned int* value);
void gameParamRun(void);

#endif
