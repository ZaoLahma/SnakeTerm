#include "../../inc/game_schd.h"
#include "../../inc/term_graphics.h"
#include "../../inc/game_input_handler.h"
#include <unistd.h>

static unsigned char running;

void gameMain()
{
	running = 1u;
	
	while(1u == running)
	{
		termGraphicsDraw();
		
		(void)getKey();
		
		usleep(1000000);
	}
}
