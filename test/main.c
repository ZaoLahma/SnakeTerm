#include "../inc/game_input_handler.h"
#include "../inc/game_schd.h"
#include <stdio.h>
#include <unistd.h>

#define MAX_NO_OF_THREADS (4u)

int main(void)
{	
	gameMain();	
	printf("Snake exit\n");
	return 0;
}