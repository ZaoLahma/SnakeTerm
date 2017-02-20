#include "../../inc/game_input_handler.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define KEY_DOWN_VAL (27u)

static unsigned char running;
static unsigned char currKey;
static struct termios old_term;
static struct termios new_term;

static void initTermios(void);
static void resetTermios(void);

void* inputHandlerMain(void* arg)
{
	printf("inputHandlerMain running\n");
	
	while(1u == running)
	{
		unsigned char keyPressed = getchar();

		if((KEY_DOWN_VAL) != keyPressed &&
		   (INPUT_HANDLER_KEY_INVALID) == currKey)
		{
			currKey = keyPressed;
		}
	}
	
	return arg;
}

static void initTermios() 
{
  tcgetattr(STDIN_FILENO, &old_term);
  new_term = old_term;
  new_term.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
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

unsigned char getKey()
{
	unsigned char retVal = currKey;
	
	currKey = INPUT_HANDLER_KEY_INVALID;
	
	return retVal;
}
