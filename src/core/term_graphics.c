#include "../../inc/term_graphics.h"
#include <stdio.h>
#include <string.h>

#define GRAPHICS_BUF_SIZE ((GRAPHICS_X_SIZE) * (GRAPHICS_Y_SIZE)) + (GRAPHICS_Y_SIZE)

static char graphicsBuf[(GRAPHICS_BUF_SIZE)];
static unsigned int printed;

void termGraphicsInit(void)
{
	(void) memset(graphicsBuf, ' ', (GRAPHICS_BUF_SIZE));
	printed = 0u;
}

void termGraphicsDraw(GraphicsEntity graphics[], unsigned int noOfEntities)
{
	printed = 1u;

    unsigned int graphicsPos = 0;

    unsigned int i = 0u;
    unsigned int x = 0u;

    memset(graphicsBuf, ' ', (GRAPHICS_BUF_SIZE));

    //Reset buffer and add all line breaks
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

    //Put all graphics elements into the buffer
    for(i = 0u; i < noOfEntities; ++i)
    {
    	printf("graphics[%u].appearance: %c\n", i, graphics[i].appearance);
        graphicsPos = graphics[i].yPos * (GRAPHICS_X_SIZE) + graphics[i].yPos + graphics[i].xPos;
        if(' ' == graphicsBuf[graphicsPos] && '\n' != graphicsBuf[graphicsPos])
        {
        	graphicsBuf[graphicsPos] = graphics[i].appearance;
        }
        else
        {
        	printf("skipping: %c\n", graphicsBuf[graphicsPos]);
        }
    }

    //Finally clear the screen and print the graphics
    printf("\n\033c");
    graphicsPos = 0u;
    for(graphicsPos = 0u; graphicsPos < GRAPHICS_BUF_SIZE; ++graphicsPos)
    {
    	printf("%c", graphicsBuf[graphicsPos]);
    }
    printf("\n");
}
