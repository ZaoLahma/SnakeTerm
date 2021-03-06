#ifndef HEADER_GAME_PARAM
#define HEADER_GAME_PARAM

typedef enum GameParamId_
{
	GAME_PARAM_HIGH_SCORE,
	GAME_PARAM_MAX_CPU_LOAD,
	GAME_PARAM_UP_KEY,
	GAME_PARAM_DOWN_KEY,
	GAME_PARAM_LEFT_KEY,
	GAME_PARAM_RIGHT_KEY,
	GAME_PARAM_NO_OF_PARAMS
} GameParamId;

void initGameParam(void);
void setGameParam(GameParamId paramId, unsigned int value);
void getGameParam(GameParamId paramId, unsigned int* value);
void gameParamRun(void);
void deInitGameParam(void);

#endif
