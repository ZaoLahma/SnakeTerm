#include "../../inc/game_schd.h"
#include "../../inc/term_graphics.h"
#include "../../inc/game_input_handler.h"
#include <unistd.h>

static unsigned char running;

static GraphicsEntity graphics[200];

void gameMain()
{
	running = 1u;
	
	/* Populate a dummy graphics buf just to test the terminal graphics */
	unsigned int i;
	unsigned int y = 0;
	char byteVal = 0x30u;
	for(y = 0; y < 10; ++y)
	{
		for(i = 0; i < 20; ++i)
		{
			unsigned int index = y * 20 + i;
			graphics[index].appearance = byteVal;
			graphics[index].xCoord = i;
			graphics[index].yCoord = y;
		}
		byteVal++;
	}
	
	while(1u == running)
	{
		termGraphicsDraw(graphics, 200);
		
		char key = getKey();
		if('s' == key)
		{
			running = 0u;
		}
		
		usleep(1000000);
	}
}
