#include "../../inc/game_input_handler.h"
#include <stdio.h>
#include <termios.h>

static unsigned char running;
static char currKey;
static struct termios old_term;
static struct termios new_term;

static void initTermios(void);
static void resetTermios(void);

void* inputHandlerMain(void* arg)
{
	printf("inputHandlerMain running\n");
	
	while(1u == running)
	{
		char keyPressed = getchar();
		
		if((INPUT_HANDLER_KEY_INVALID) == currKey)
		{
			currKey = keyPressed;
		}
	}
	
	return arg;
}

static void initTermios() 
{
  tcgetattr(0, &old_term);
  new_term = old_term;
  new_term.c_lflag &= ~ICANON;
  new_term.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &new_term);
}

static void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old_term);
}

void initInputHandler(void)
{	
	initTermios();
	
	currKey = (INPUT_HANDLER_KEY_INVALID);
	
	running = 1u;
}

void stopInputHandler(void)
{
	running = 0u;
	resetTermios();	
}

char getKey()
{
	char retVal = currKey;
	
	currKey = INPUT_HANDLER_KEY_INVALID;
	
	return retVal;
}
