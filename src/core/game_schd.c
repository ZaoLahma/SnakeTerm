#include "../../inc/game_schd.h"
#include "../../inc/game_input_handler.h"
#include "../../inc/game_snake.h"
#include "../../inc/game_time.h"
#include <unistd.h>
#include <stdint.h>

static unsigned char running;

#define SECOND_IN_USECONDS (1000000u)
#define FRAMES_PER_SECOND  (10u)

void gameMain()
{
	running = 1u;
	
	initInputHandler();
	
	initSnake();
	
	uint64_t timeBefore = 0u;
	uint64_t timeAfter =  0u;
	uint64_t timeDiff =   0u;

	while(1u == running)
	{
		timeBefore = getGameMicroSecTime();
		snakeRun();
		timeAfter = getGameMicroSecTime();

		timeDiff = timeAfter - timeBefore;

		usleep(((SECOND_IN_USECONDS) / (FRAMES_PER_SECOND)) -
				timeDiff);
	}
	
	stopInputHandler();
}

void gameStop(void)
{
	running = 0u;
}
