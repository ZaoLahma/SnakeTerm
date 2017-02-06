#include "../../inc/term_graphics.h"
#include <stdio.h>

#define GRAPHICS_BUF_SIZE ((GRAPHICS_X_SIZE) * (GRAPHICS_Y_SIZE)) + (GRAPHICS_Y_SIZE)

static char graphicsBuf[(GRAPHICS_BUF_SIZE)];


void termGraphicsDraw(GraphicsEntity graphics[], unsigned int noOfEntities)
{
	unsigned int displayLength = ((GRAPHICS_X_SIZE) * (GRAPHICS_Y_SIZE));
	unsigned int i;
	unsigned int rowIndex = 0;
	
	for(i = 0; i < noOfEntities; ++i)
	{
		unsigned int bufIndex = (GRAPHICS_X_SIZE) * graphics[i].yPos + graphics[i].xPos;
		if(bufIndex < (GRAPHICS_BUF_SIZE))
		{
			graphicsBuf[bufIndex] = graphics[i].appearance;
		}
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
	
	printf("\033[2J%s\n", graphicsBuf);
}
