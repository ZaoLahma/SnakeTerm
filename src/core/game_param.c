#include "../../inc/game_param.h"
#include <stdio.h>

typedef struct GameParamDescriptor_
{
	GameParamId id;
	unsigned int ramValue;
	unsigned int fileValue;
	unsigned int paramByteAddress;
} GameParamDescriptor;

static GameParamDescriptor paramDescriptors[] =
{
		{GAME_PARAM_HIGH_SCORE, 0, 0, 0}
};

static FILE* paramFile;

void initGameParam(void)
{
	paramFile = fopen("gameParams.bin", "rb");

	if(paramFile)
	{
		unsigned int paramIndex = 0u;
		GameParamDescriptor* descriptor;
		for( ; paramIndex < GAME_PARAM_NO_OF_PARAMS; ++paramIndex)
		{
			descriptor = &paramDescriptors[paramIndex];
			fseek(paramFile, descriptor->paramByteAddress, SEEK_SET);
			fread(&descriptor->fileValue, sizeof(descriptor->ramValue), 1, paramFile);
			descriptor->ramValue = descriptor->fileValue;
		}
		fclose(paramFile);
	}


	paramFile = fopen("gameParams.bin", "wb");

}

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

void gameParamRun(void)
{
	unsigned int paramIndex = 0u;
	GameParamDescriptor* descriptor;

	for( ; paramIndex < GAME_PARAM_NO_OF_PARAMS; ++paramIndex)
	{
		descriptor = &paramDescriptors[paramIndex];
		if(descriptor->ramValue != descriptor->fileValue)
		{
			fseek(paramFile, descriptor->paramByteAddress, SEEK_SET);
			fwrite(&descriptor->ramValue, sizeof(descriptor->ramValue), 1, paramFile);
			descriptor->fileValue = descriptor->ramValue;
		}
	}
}
