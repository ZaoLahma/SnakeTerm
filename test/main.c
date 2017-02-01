#include "../inc/game_input_handler.h"
#include "../inc/game_schd.h"
#include "../inc/thread_pool.h"
#include <stdio.h>
#include <unistd.h>

#define MAX_NO_OF_THREADS (4u)

int main(void)
{
	struct ThreadContext* threadContext = init_thread_pool((MAX_NO_OF_THREADS));
	
	initInputHandler(threadContext);
	
	gameMain();
	
	return 0;
}
