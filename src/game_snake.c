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

#define UP    (-1u)
#define DOWN  (1u)
#define LEFT  (-1u)
#define RIGHT (1u)

typedef struct Snake_
{
	unsigned int xPos;
	unsigned int yPos;
	unsigned int length;
	unsigned int direction;
} Snake;

static GraphicsEntity snakeGraphics[(NUM_GRAPHICAL_ENTITIES)];
static Snake snake = { 10, 10, 3, DOWN};
static unsigned int snakeGraphicsStart;

static void moveSnake(void);

static void moveSnake(void)
{
	if((UP) == snake.direction)
	{
		snakeGraphics[snakeGraphicsStart].yPos += -1u;
	}

	if((DOWN) == snake.direction)
	{
		snakeGraphics[snakeGraphicsStart].yPos += 1u;
	}

	if((LEFT) == snake.direction)
	{
		snakeGraphics[snakeGraphicsStart].xPos += -1u;
	}

	if((RIGHT) == snake.direction)
	{
		snakeGraphics[snakeGraphicsStart].xPos += 1u;
	}

	unsigned int i = 1u;
	for( ; i < snake.length; ++i)
	{
		snakeGraphics[snakeGraphicsStart + i] = snakeGraphics[snakeGraphicsStart + i - 1u];
		snakeGraphics[snakeGraphicsStart + i].appearance = '*';
	}
}

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

	snakeGraphicsStart = graphicsIndex;

	printf("snakeGraphicsStart: %u\n", snakeGraphicsStart);

	snakeGraphics[snakeGraphicsStart].appearance = '@';
	snakeGraphics[snakeGraphicsStart].xPos = snake.xPos;
	snakeGraphics[snakeGraphicsStart].yPos = snake.yPos;

	unsigned int snakeBodyIndex = 1u;

	for( ; snakeBodyIndex < snake.length; ++snakeBodyIndex)
	{
		snakeGraphics[snakeGraphicsStart + snakeBodyIndex] = snakeGraphics[snakeGraphicsStart + snakeBodyIndex - 1u];
		snakeGraphics[snakeGraphicsStart + snakeBodyIndex].appearance = '*';
		snakeGraphics[snakeGraphicsStart + snakeBodyIndex].xPos = snakeGraphics[snakeGraphicsStart + snakeBodyIndex - 1u].xPos - 1u;

		printf("body: %c (%u) - xPos: %u\n",
				snakeGraphics[snakeGraphicsStart + snakeBodyIndex].appearance,
				snakeGraphicsStart + snakeBodyIndex,
				snakeGraphics[snakeGraphicsStart + snakeBodyIndex].xPos );
	}
}

void snakeRun(void)
{
	termGraphicsDraw(snakeGraphics, (NUM_GRAPHICAL_ENTITIES));
	unsigned char key = getKey();
	
	moveSnake();

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
