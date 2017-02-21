#include "../inc/game_snake.h"
#include "../inc/term_graphics.h"
#include "../inc/game_input_handler.h"
#include <stdio.h>

#define HORIZONTAL_WALL_LENGTH ((GRAPHICS_X_SIZE))
#define VERTICAL_WALL_LENGTH ((GRAPHICS_Y_SIZE))
#define SNAKE_MAX_LENGTH ((HORIZONTAL_WALL_LENGTH) * (VERTICAL_WALL_LENGTH))
#define NUM_GRAPHICAL_ENTITIES (((HORIZONTAL_WALL_LENGTH) * (VERTICAL_WALL_LENGTH)))
#define NUM_WALL_ENTITIES (((HORIZONTAL_WALL_LENGTH) * 2u) + ((VERTICAL_WALL_LENGTH) * 2u))

#define SNAKE_UP    (119u)
#define SNAKE_DOWN  (115u)
#define SNAKE_LEFT  (97u)
#define SNAKE_RIGHT (100u)

static GraphicsEntity snakeGraphics[(NUM_GRAPHICAL_ENTITIES)];

void initSnake(void)
{

	termGraphicsInit();

	/* Set up the initial play field */
	
	unsigned int i = 0u;
	unsigned int xPos = 0u;
	unsigned int yPos = 0u;
	
	printf("Num graphical entities: %d\n", (NUM_GRAPHICAL_ENTITIES));

	i = 0u;
	xPos = 0u;
	yPos = 0u;
	unsigned int graphicsIndex = 0u;

	for( ; i < (NUM_GRAPHICAL_ENTITIES); ++i)
	{

		if(xPos == 0u || xPos == (HORIZONTAL_WALL_LENGTH - 1u))
		{
			printf("Added horizontal wall at (%u, %u)\n", xPos, yPos);
			snakeGraphics[graphicsIndex].appearance = '|';
			snakeGraphics[graphicsIndex].xPos = xPos;
			snakeGraphics[graphicsIndex].yPos = yPos;
			graphicsIndex++;
		}
		else if(yPos == 0 || yPos == (VERTICAL_WALL_LENGTH - 1u))
		{
			printf("Added vertical wall at (%u, %u)\n", xPos, yPos);
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

		if(key == (SNAKE_UP))
		{
			printf("SNAKE_UP\n");
		}
		if(key == (SNAKE_DOWN))
		{
			printf("SNAKE_DOWN\n");
		}
		if(key == (SNAKE_LEFT))
		{
			printf("SNAKE_LEFT\n");
		}
		if(key == (SNAKE_RIGHT))
		{
			printf("SNAKE_RIGHT\n");
		}
	}
}
