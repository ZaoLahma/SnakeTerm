#include "../../inc/game_schd.h"
#include "../../inc/game_input_handler.h"
#include "../../inc/game_snake.h"
#include <pthread.h>
#include <unistd.h>

static unsigned char running;

//static GraphicsEntity graphics[200];

void gameMain()
{
	running = 1u;
	
	/* Start the input handler */
	
	initInputHandler();
	
	pthread_t inputThread;
	(void)pthread_create(&inputThread, 0u, &inputHandlerMain, 0u);
	
	initSnake();
	
	while(1u == running)
	{
		snakeRun();
		
		char key = getKey();
		if('s' == key)
		{
			running = 0u;
		}
		
		usleep(1000000);
	}
	
	stopInputHandler();
	
	pthread_join(inputThread, 0u);
}
