#include "../inc/game_snake.h"
#include "../inc/term_graphics.h"
#include "../inc/game_input_handler.h"
#include "../inc/game_schd.h"
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

#define QUIT ('q')

typedef struct Snake_
{
	unsigned int xPos;
	unsigned int yPos;
	unsigned int length;
	unsigned int direction;
} Snake;

static GraphicsEntity snakeGraphics[(NUM_GRAPHICAL_ENTITIES)];
static Snake snake = { 10, 10, 4, SNAKE_DOWN};
static unsigned int snakeGraphicsStart;

static void renderSnake(void);
static void checkBoundaries(void);

static void renderSnake(void)
{
	unsigned int snakeBodyIndex = snake.length - 1u;

	for( ; snakeBodyIndex >= 1u; snakeBodyIndex--)
	{
		snakeGraphics[snakeGraphicsStart + snakeBodyIndex] = snakeGraphics[snakeGraphicsStart + snakeBodyIndex - 1u];
		snakeGraphics[snakeGraphicsStart + snakeBodyIndex].appearance = '*';
	}

	if((SNAKE_UP) == snake.direction)
	{
		snake.yPos += -1u;
	}

	if((SNAKE_DOWN) == snake.direction)
	{
		snake.yPos += 1u;
	}

	if((SNAKE_LEFT) == snake.direction)
	{
		snake.xPos += -1u;
	}

	if((SNAKE_RIGHT) == snake.direction)
	{
		snake.xPos += 1u;
	}

	snakeGraphics[snakeGraphicsStart].appearance = '@';
	snakeGraphics[snakeGraphicsStart].xPos = snake.xPos;
	snakeGraphics[snakeGraphicsStart].yPos = snake.yPos;
}

static void checkBoundaries(void)
{
	if(snake.xPos == 0u || snake.xPos == ((HORIZONTAL_WALL_LENGTH) - 1u) ||
	   snake.yPos == 0u || snake.yPos == ((VERTICAL_WALL_LENGTH) - 1u))
	{
		initSnake();
	}
}

void initSnake(void)
{
	termGraphicsInit();

	/* Set up the initial play field */
	
	unsigned int i = 0u;
	unsigned int xPos = 0u;
	unsigned int yPos = 0u;

	i = 0u;
	xPos = 0u;
	yPos = 0u;
	unsigned int graphicsIndex = 0u;

	for( ; i < (NUM_GRAPHICAL_ENTITIES); ++i)
	{

		if(xPos == 0u || xPos == (HORIZONTAL_WALL_LENGTH - 1u))
		{
			snakeGraphics[graphicsIndex].appearance = '|';
			snakeGraphics[graphicsIndex].xPos = xPos;
			snakeGraphics[graphicsIndex].yPos = yPos;
			graphicsIndex++;
		}
		else if(yPos == 0 || yPos == (VERTICAL_WALL_LENGTH - 1u))
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
			xPos = 0;
		}
	}

	snake.xPos = 10u;
	snake.yPos = 10u;
	snake.direction = (SNAKE_DOWN);

	snakeGraphicsStart = graphicsIndex;

	snakeGraphics[snakeGraphicsStart].appearance = '@';
	snakeGraphics[snakeGraphicsStart].xPos = snake.xPos;
	snakeGraphics[snakeGraphicsStart].yPos = snake.yPos;

	unsigned int snakeBodyIndex = 1u;

	for( ; snakeBodyIndex < snake.length; ++snakeBodyIndex)
	{
		snakeGraphics[snakeGraphicsStart + snakeBodyIndex] = snakeGraphics[snakeGraphicsStart + snakeBodyIndex - 1u];
		snakeGraphics[snakeGraphicsStart + snakeBodyIndex].appearance = '*';
		snakeGraphics[snakeGraphicsStart + snakeBodyIndex].xPos = snakeGraphics[snakeGraphicsStart + snakeBodyIndex - 1u].xPos - 1u;
	}
}

void snakeRun(void)
{
	unsigned char key = getKey();
	if((INPUT_HANDLER_KEY_INVALID) != key)
	{
		if(((SNAKE_DOWN) == snake.direction && key != (SNAKE_UP)) ||
		   ((SNAKE_UP) == snake.direction && key != (SNAKE_DOWN)) ||
		   ((SNAKE_RIGHT) == snake.direction && key != (SNAKE_LEFT)) ||
		   ((SNAKE_LEFT) == snake.direction && key != (SNAKE_RIGHT)))
		{
			snake.direction = key;
		}

		if(key == (QUIT))
		{
			stop();
		}
	}
	renderSnake();
	termGraphicsDraw(snakeGraphics, (NUM_GRAPHICAL_ENTITIES));
	checkBoundaries();
}
