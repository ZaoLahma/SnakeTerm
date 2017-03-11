#include "../../inc/game_schd.h"
#include "../../inc/game_input_handler.h"
#include "../../inc/game_snake.h"
#include "../../inc/game_time.h"
#include "../../inc/game_param.h"
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

static unsigned char running;

#define SECOND_IN_USECONDS    (1000000u)
#define FRAMES_PER_SECOND     (10u)
#define PERCENTAGE_MULTIPLIER (100u)

static double cpuUtilizationPercentage;

double getCpuUtilizationPercentage(void)
{
	return cpuUtilizationPercentage;
}

void gameMain()
{
	running = 1u;
	
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
		gameParamRun();
		timeAfter = getGameMicroSecTime();

		timeDiff = timeAfter - timeBefore;

		useconds_t toSleep = (SECOND_IN_USECONDS) / (FRAMES_PER_SECOND);

		cpuUtilizationPercentage = (PERCENTAGE_MULTIPLIER) * (timeDiff / toSleep);

		usleep(toSleep - timeDiff);
	}
	
	stopInputHandler();
}

void gameStop(void)
{
	running = 0u;
}
