#include "../../inc/term_graphics.h"
#include <stdio.h>
#include <string.h>

#define GRAPHICS_BUF_SIZE ((GRAPHICS_X_SIZE) * (GRAPHICS_Y_SIZE)) + (GRAPHICS_Y_SIZE)

static char graphicsBuf[(GRAPHICS_BUF_SIZE)];
static char printed = 0u;

void termGraphicsDraw(GraphicsEntity graphics[], unsigned int noOfEntities)
{
	unsigned int i;
	unsigned int rowIndex = 0;
	
	for(i = 0; i < noOfEntities; ++i)
	{
		unsigned int bufIndex = (GRAPHICS_X_SIZE) * graphics[i].yPos + graphics[i].xPos;
		//printf("Adding element to index: %u (x: %u, y: %u\n", bufIndex, graphics[i].xPos, graphics[i].yPos);
		if(bufIndex < (GRAPHICS_BUF_SIZE))
		{
			graphicsBuf[bufIndex] = graphics[i].appearance;
		}
	}
	
	for(i = 0; i < (GRAPHICS_BUF_SIZE); i++)
	{	
		if(rowIndex == (GRAPHICS_X_SIZE))
		{
			rowIndex = 0;
			memmove(&graphicsBuf[i + 1u], &graphicsBuf[i], (GRAPHICS_BUF_SIZE) - i);
			graphicsBuf[i] = '\n';
		}
		else
		{
			rowIndex++;
		}
	}
	
	//printf("\033[2J%s\n", graphicsBuf);
	
	if(0u == printed)
	{
		printf("\n%s\n", graphicsBuf);
		printed = 1u;
	}
}
