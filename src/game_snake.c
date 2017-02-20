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

	termGraphicsInit();

	/* Set up the initial play field */
	
	unsigned int i = 0u;
	unsigned int xPos = 0u;
	unsigned int yPos = 0u;
	
	printf("Num graphical entities: %d\n", (NUM_GRAPHICAL_ENTITIES));

	for( ; i < (NUM_GRAPHICAL_ENTITIES); ++i)
	{
		snakeGraphics[i].appearance = '*';
		snakeGraphics[i].xPos = xPos;
		snakeGraphics[i].yPos = yPos;

		xPos++;
		
		if(xPos == (HORIZONTAL_WALL_LENGTH))
		{
			xPos = 0u;
			yPos++;
		}
	}

	i = 0u;
	xPos = 0u;
	yPos = 0u;
	unsigned int graphicsIndex = 0u;

	for( ; i < (NUM_GRAPHICAL_ENTITIES); ++i)
	{
		if(yPos == 0)
		{
			snakeGraphics[graphicsIndex].appearance = '-';
			snakeGraphics[graphicsIndex].xPos = xPos;
			snakeGraphics[graphicsIndex].yPos = yPos;
			graphicsIndex++;
		}

		if(xPos == 0u)
		{
			snakeGraphics[graphicsIndex].appearance = '|';
			snakeGraphics[graphicsIndex].xPos = xPos;
			snakeGraphics[graphicsIndex].yPos = yPos;
			graphicsIndex++;
		}

		if(xPos == (HORIZONTAL_WALL_LENGTH - 1u))
		{
			snakeGraphics[graphicsIndex].appearance = '|';
			snakeGraphics[graphicsIndex].xPos = xPos;
			snakeGraphics[graphicsIndex].yPos = yPos;
			graphicsIndex++;
		}

		if(yPos == (VERTICAL_WALL_LENGTH - 1u))
		{
			snakeGraphics[graphicsIndex].appearance = '-';
			snakeGraphics[graphicsIndex].xPos = xPos;
			snakeGraphics[graphicsIndex].yPos = yPos;
			graphicsIndex++;
		}

		xPos++;

		if(xPos == (HORIZONTAL_WALL_LENGTH))
		{
			yPos++;
			printf("yPos: %u, wall length: %u\n", yPos, (VERTICAL_WALL_LENGTH));
			xPos = 0;
		}
	}
}

void snakeRun(void)
{
	termGraphicsDraw(snakeGraphics, (NUM_GRAPHICAL_ENTITIES));
	unsigned char key = getKey();
	
	if((INPUT_HANDLER_KEY_INVALID) != key)
	{
		(void) printf("key: %u\n", key);
	}
}
