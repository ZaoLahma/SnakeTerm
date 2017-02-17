#include "../inc/game_snake.h"
#include "../inc/term_graphics.h"
#include "../inc/game_input_handler.h"
#include <stdio.h>

#define HORIZONTAL_WALL_LENGTH ((GRAPHICS_X_SIZE))
#define VERTICAL_WALL_LENGTH ((GRAPHICS_Y_SIZE))
#define SNAKE_MAX_LENGTH ((HORIZONTAL_WALL_LENGTH) * (VERTICAL_WALL_LENGTH))
#define NUM_GRAPHICAL_ENTITIES (((HORIZONTAL_WALL_LENGTH) * (VERTICAL_WALL_LENGTH)))
#define NUM_WALL_ENTITIES (((HORIZONTAL_WALL_LENGTH) * 2u) + ((VERTICAL_WALL_LENGTH) * 2u))

static GraphicsEntity snakeGraphics[(NUM_GRAPHICAL_ENTITIES)];

void initSnake(void)
{
	/* Set up the initial play field */
	
	unsigned int i = 0u;
	unsigned int xPos = 0u;
	unsigned int yPos = 0u;
	
	printf("Num graphical entities: %d\n", (NUM_GRAPHICAL_ENTITIES));
	
	for( ; i < (NUM_GRAPHICAL_ENTITIES); ++i)
	{
		snakeGraphics[i].appearance = ' ';
		snakeGraphics[i].xPos = xPos;
		snakeGraphics[i].yPos = yPos;
		
		xPos++;
		
		if(xPos == (HORIZONTAL_WALL_LENGTH))
		{
			xPos = 0u;
			yPos++;
		}
	}
	
	xPos = 0u;
	yPos = 0u;
	unsigned int graphicsPos = 0u;	
	
	for(i = 0u; i < (NUM_GRAPHICAL_ENTITIES); ++i)
	{
		snakeGraphics[graphicsPos].appearance = ' ';
		snakeGraphics[graphicsPos].xPos = xPos;
		snakeGraphics[graphicsPos].yPos = yPos;		
		
		if(0u == yPos)
		{
			snakeGraphics[graphicsPos].appearance = '-';
			graphicsPos++;
		}
		
		if(0u == xPos)
		{
			printf("Vertical line yPos: %u\n", yPos);
			snakeGraphics[graphicsPos].appearance = '|';
			graphicsPos++;
		}
		
		xPos++;
		if(xPos == (HORIZONTAL_WALL_LENGTH))
		{
			xPos = 0;
			yPos++;
			
			printf("New line\n");
			
			snakeGraphics[graphicsPos + 1] = snakeGraphics[graphicsPos];
			snakeGraphics[graphicsPos].appearance = '\n';
			graphicsPos++;
			graphicsPos++;
		}
		
		printf("graphicsPos: %u\n", graphicsPos);
		printf("xPos: %u, yPos: %u\n", xPos, yPos);
	}
}

void snakeRun(void)
{
	termGraphicsDraw(snakeGraphics, (NUM_GRAPHICAL_ENTITIES));
	char key = getKey();
	
	if((INPUT_HANDLER_KEY_INVALID) != key)
	{
		(void) printf("key: %u\n", key);
	}
}
