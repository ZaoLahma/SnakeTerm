#include "../../inc/term_graphics.h"
#include <stdio.h>

#define GRAPHICS_Y_SIZE (10u)
#define GRAPHICS_X_SIZE (20u)

static char graphicsBuf[((GRAPHICS_X_SIZE) * (GRAPHICS_Y_SIZE)) + (GRAPHICS_Y_SIZE)];


void termGraphicsDraw(GraphicsEntity graphics[], unsigned int noOfEntities)
{
	unsigned int displayLength = ((GRAPHICS_X_SIZE) * (GRAPHICS_Y_SIZE));
	unsigned int i;
	unsigned int rowIndex = 0;
	
	for(i = 0; i < noOfEntities; ++i)
	{
		unsigned int bufIndex = (GRAPHICS_X_SIZE) * graphics[i].yCoord + graphics[i].xCoord;
		graphicsBuf[bufIndex] = graphics[i].appearance;
	}
	
	for(i = 0; i < displayLength; i++)
	{	
		if(rowIndex == (GRAPHICS_X_SIZE) - 1u)
		{
			rowIndex = 0;
			graphicsBuf[i] = '\n';
		}
		else
		{
			rowIndex++;
		}
	}
	
	printf("\033[2J%s", graphicsBuf);
}
