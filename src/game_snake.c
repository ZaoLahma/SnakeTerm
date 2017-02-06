#include "../inc/game_snake.h"
#include "../inc/term_graphics.h"

#define HORIZONTAL_WALL_LENGTH ((GRAPHICS_X_SIZE))
#define VERTICAL_WALL_LENGTH ((GRAPHICS_Y_SIZE))
#define SNAKE_MAX_LENGTH ((HORIZONTAL_WALL_LENGTH) * (VERTICAL_WALL_LENGTH))
#define NUM_GRAPHICAL_ENTITIES (((HORIZONTAL_WALL_LENGTH) * (VERTICAL_WALL_LENGTH)))

static GraphicsEntity snakeGraphics[(NUM_GRAPHICAL_ENTITIES)];

void initSnake(void)
{
	/* Set up the initial play field */
	
	unsigned int i = 0u;
	unsigned int xPos = 0u;
	unsigned int yPos = 0u;
	
	for(i = 0u; i < (NUM_GRAPHICAL_ENTITIES); ++i)
	{
		snakeGraphics[i].appearance = ' ';
		snakeGraphics[i].xPos = xPos;
		snakeGraphics[i].yPos = yPos;
		
		if(0u == yPos)
		{
			snakeGraphics[i].appearance = '-';
		}
		if(yPos == (VERTICAL_WALL_LENGTH) - 2u)
		{
			snakeGraphics[i].appearance = '-';
		}				
		if(0u == xPos && yPos < (VERTICAL_WALL_LENGTH) - 1u)
		{
			snakeGraphics[i].appearance = '|';
		}
		if(xPos == (HORIZONTAL_WALL_LENGTH) - 2u)
		{
			snakeGraphics[i].appearance = '|';
		}
		
		xPos++;
		if(xPos > (HORIZONTAL_WALL_LENGTH))
		{
			xPos = 0;
			yPos++;
		}
	}
}

void snakeRun(void)
{
	termGraphicsDraw(snakeGraphics, (NUM_GRAPHICAL_ENTITIES));
}
