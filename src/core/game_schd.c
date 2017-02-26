#include "../../inc/game_schd.h"
#include "../../inc/game_input_handler.h"
#include "../../inc/game_snake.h"
#include "../../inc/game_time.h"
#include <unistd.h>
#include <stdint.h>

static unsigned char running;

#define SECOND_IN_USECONDS (1000000u)
#define FRAMES_PER_SECOND  (20u)

void gameMain()
{
	running = 1u;
	
	initInputHandler();
	
	initSnake();
	
	uint64_t timeBefore;
	uint64_t timeAfter;

	while(1u == running)
	{
		timeBefore = getGameMicroSecTime();
		snakeRun();
		timeAfter = getGameMicroSecTime();
		usleep(((SECOND_IN_USECONDS) / (FRAMES_PER_SECOND)) -
				(timeAfter - timeBefore));
	}
	
	stopInputHandler();
}

void stop(void)
{
	running = 0u;
}
