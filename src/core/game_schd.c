#include "../../inc/game_schd.h"
#include "../../inc/game_input_handler.h"
#include "../../inc/game_snake.h"
#include <unistd.h>

static unsigned char running;

#define SECOND_IN_USECONDS (1000000u)
#define FRAMES_PER_SECOND  (5u)

void gameMain()
{
	running = 1u;
	
	initInputHandler();
	
	initSnake();
	
	while(1u == running)
	{
		snakeRun();
		usleep((SECOND_IN_USECONDS) / (FRAMES_PER_SECOND));
	}
	
	stopInputHandler();
}

void stop(void)
{
	running = 0u;
}
