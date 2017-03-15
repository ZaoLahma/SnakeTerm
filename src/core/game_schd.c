#include "../../inc/game_schd.h"
#include "../../inc/game_input_handler.h"
#include "../../inc/game_snake.h"
#include "../../inc/game_time.h"
#include "../../inc/game_param.h"
#include "../../inc/game_state.h"
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

#define SECOND_IN_USECONDS      (1000000u)
#define FRAMES_PER_SECOND       (10u)
#define PERCENTAGE_MULTIPLIER   (100u)
#define CPU_LOAD_MULTIPLIER     (1000.0f)
#define GAME_SECONDS_TICK_CYCLE (10u)
#define GAME_PARAM_WRITE_CYCLE  (2u)

static unsigned char running;
static float cpuLoadPercentage;
static unsigned int runCnt = 0u;

float getCpuLoadPercentage(void)
{
	return cpuLoadPercentage;
}

float getCpuLoadMaxPercentage(void)
{
	unsigned int cpuMaxLoad = 0u;

	getGameParam(GAME_PARAM_MAX_CPU_LOAD, &cpuMaxLoad);

	float cpuMaxLoadPercentage = (float)(cpuMaxLoad / (CPU_LOAD_MULTIPLIER));

	return cpuMaxLoadPercentage;
}

void gameMain()
{
	running = 1u;
	
	initGameState();
	initInputHandler();
	initGameParam();
	initSnake();
	
	uint64_t timeBefore = 0u;
	uint64_t timeAfter =  0u;
	double timeDiff =   0u;

	while(1u == running)
	{
		timeBefore = getGameMicroSecTime();

		snakeRun();
		if(0u == runCnt % ((FRAMES_PER_SECOND) * (GAME_PARAM_WRITE_CYCLE)))
		{
			gameParamRun();
		}

		timeAfter = getGameMicroSecTime();
		timeDiff = timeAfter - timeBefore;

		useconds_t toSleep = (SECOND_IN_USECONDS) / (FRAMES_PER_SECOND);

		cpuLoadPercentage = (PERCENTAGE_MULTIPLIER) * (timeDiff / toSleep);
		unsigned int cpuMaxLoad = 0u;
		getGameParam(GAME_PARAM_MAX_CPU_LOAD, &cpuMaxLoad);
		if((unsigned int)(cpuLoadPercentage * (CPU_LOAD_MULTIPLIER)) > cpuMaxLoad)
		{
			cpuMaxLoad = (unsigned int)(cpuLoadPercentage * (CPU_LOAD_MULTIPLIER));

			setGameParam(GAME_PARAM_MAX_CPU_LOAD, cpuMaxLoad);
		}

		usleep(toSleep - timeDiff);

		runCnt = (runCnt + 1u) % ((FRAMES_PER_SECOND) * (GAME_SECONDS_TICK_CYCLE));
	}
	
	stopInputHandler();

	deInitGameParam();
}

void gameStop(void)
{
	running = 0u;
}
