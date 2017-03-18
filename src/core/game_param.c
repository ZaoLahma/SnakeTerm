#include "../../inc/game_param.h"
#include "../../inc/game_state.h"
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
		{GAME_PARAM_HIGH_SCORE, 0, 0, 0x0},
		{GAME_PARAM_MAX_CPU_LOAD, 0, 0, 0x4},
		{GAME_PARAM_UP_KEY, 65, 0, 0x8},
		{GAME_PARAM_DOWN_KEY, 66, 0, 0xc},
		{GAME_PARAM_LEFT_KEY, 68, 0, 0x10},
		{GAME_PARAM_RIGHT_KEY, 67, 0, 0x14}
};

static FILE* paramFile;

static void flushParam(GameParamDescriptor* descriptor);

static void flushParam(GameParamDescriptor* descriptor)
{
	fseek(paramFile, descriptor->paramByteAddress, SEEK_SET);
	descriptor->fileValue = descriptor->ramValue;
	fwrite(&descriptor->fileValue, sizeof(descriptor->fileValue), 1, paramFile);
}

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
			fread(&descriptor->fileValue, sizeof(descriptor->fileValue), 1, paramFile);
			descriptor->ramValue = descriptor->fileValue;
		}
		fclose(paramFile);
	}

	paramFile = fopen("gameParams.bin", "wb");

}

void setGameParam(GameParamId paramId, unsigned int value)
{
	GameParamDescriptor* descriptor = &paramDescriptors[paramId];

	descriptor->ramValue = value;
}

void getGameParam(GameParamId paramId, unsigned int* value)
{
	GameParamDescriptor* descriptor = &paramDescriptors[paramId];

	*value = descriptor->ramValue;
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
			flushParam(descriptor);
		}
	}
}

void deInitGameParam(void)
{
	unsigned int paramIndex = 0u;
	GameParamDescriptor* descriptor;

	for( ; paramIndex < GAME_PARAM_NO_OF_PARAMS; ++paramIndex)
	{
		descriptor = &paramDescriptors[paramIndex];
		flushParam(descriptor);
	}
	fclose(paramFile);
}
