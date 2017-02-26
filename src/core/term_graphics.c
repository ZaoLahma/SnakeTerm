#include "../../inc/term_graphics.h"
#include <stdio.h>
#include <string.h>

#define GRAPHICS_BUF_SIZE ((GRAPHICS_X_SIZE) * (GRAPHICS_Y_SIZE)) + (GRAPHICS_Y_SIZE)

static char graphicsBuf[(GRAPHICS_BUF_SIZE)];

void termGraphicsInit(void)
{
	(void) memset(graphicsBuf, ' ', (GRAPHICS_BUF_SIZE));
}

void termGraphicsDraw(GraphicsEntity graphics[], unsigned int noOfEntities)
{
    unsigned int graphicsPos = 0;

    unsigned int i = 0u;
    unsigned int x = 0u;

    /* Reset buffer and add all line breaks */
    memset(graphicsBuf, ' ', (GRAPHICS_BUF_SIZE));

    for(i = 0u; i < (GRAPHICS_BUF_SIZE); ++i)
    {
        x++;
        if(x == (GRAPHICS_X_SIZE))
        {
        	i++;
        	graphicsBuf[i] = '\n';
        	x = 0;
        }
    }

    /* Put all graphics elements into the buffer */
    for(i = 0u; i < noOfEntities; ++i)
    {
        graphicsPos = graphics[i].yPos * (GRAPHICS_X_SIZE) + graphics[i].yPos + graphics[i].xPos;
        if(' ' == graphicsBuf[graphicsPos] && '\n' != graphicsBuf[graphicsPos])
        {
        	graphicsBuf[graphicsPos] = graphics[i].appearance;
        }
    }

    /* Finally clear the screen and print the graphics */
    printf("\n\033c");
    graphicsPos = 0u;
    for(graphicsPos = 0u; graphicsPos < GRAPHICS_BUF_SIZE; ++graphicsPos)
    {
    	printf("%c", graphicsBuf[graphicsPos]);
    }
    printf("\n");
}
