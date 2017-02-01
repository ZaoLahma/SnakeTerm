#include "../../inc/term_graphics.h"
#include <stdio.h>

#define GRAPHICS_Y_SIZE (10u)
#define GRAPHICS_X_SIZE (20u)

static char graphicsBuf[((GRAPHICS_X_SIZE) * (GRAPHICS_Y_SIZE)) + (GRAPHICS_Y_SIZE)];


void termGraphicsDraw(void)
{
	unsigned int displayLength = ((GRAPHICS_X_SIZE) * (GRAPHICS_Y_SIZE));
	unsigned int i;
	unsigned int rowIndex = 0;
	
	for(i = 0; i < displayLength; i++)
	{
		graphicsBuf[i] = 'x';
		
		if(rowIndex == (GRAPHICS_X_SIZE) - 1u)
		{
			rowIndex = 0;
			graphicsBuf[i] = '\n';
		}
		else
		{
			/* Find out if any game object coord corresponds 
			 * to this coord and print here */
			rowIndex++;
		}
	}
	
	printf("\033[2J%s\n\n", graphicsBuf);
}
