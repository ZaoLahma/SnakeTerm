#include "../../inc/game_param.h"

typedef struct GameParamDescriptor_
{
	GameParamId id;
	unsigned int ramValue;
	unsigned int fileValue;
} GameParamDescriptor;

static GameParamDescriptor paramDescriptors[] =
{
		{GAME_PARAM_HIGH_SCORE, 0, 0}
};

unsigned int setGameParam(GameParamId paramId, unsigned int value)
{
	GameParamDescriptor* descriptor = &paramDescriptors[paramId];

	descriptor->ramValue = value;

	return 0;
}

unsigned int getGameParam(GameParamId paramId, unsigned int* value)
{
	GameParamDescriptor* descriptor = &paramDescriptors[paramId];

	*value = descriptor->ramValue;

	return 0;
}
