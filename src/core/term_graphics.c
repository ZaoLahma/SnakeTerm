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

    //Reset buffer
    for(i = 0u; i < (GRAPHICS_BUF_SIZE); ++i)
    {
        graphicsBuf[i] = ' ';
    }

    //Start putting all objects into the buffer
    for(i = 0u; i < noOfEntities; ++i)
    {
        graphicsPos = graphics[i].yPos * (GRAPHICS_X_SIZE) + 2u * graphics[i].yPos + graphics[i].xPos;
        graphicsBuf[graphicsPos] = graphics[i].appearance;
    }

    //Add line breaks
    graphicsPos = 0;
    unsigned int y = 0u;
    for(y = 0u; y <= (GRAPHICS_Y_SIZE); ++y)
    {
        graphicsBuf[((GRAPHICS_X_SIZE) + 1u + y * (GRAPHICS_X_SIZE) + 2u * y)] = '\n';
    }

    printf("\033c%s\n", graphicsBuf);
}
