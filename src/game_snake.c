#include "../inc/game_snake.h"
#include "../inc/term_graphics.h"
#include "../inc/game_input_handler.h"
#include "../inc/game_schd.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define HORIZONTAL_WALL_LENGTH ((GRAPHICS_X_SIZE))
#define VERTICAL_WALL_LENGTH ((GRAPHICS_Y_SIZE))
#define SNAKE_MAX_LENGTH ((HORIZONTAL_WALL_LENGTH) * (VERTICAL_WALL_LENGTH))
#define SNAKE_MAX_FOOD_ITEMS (20u)

#define NUM_GRAPHICAL_ENTITIES ((HORIZONTAL_WALL_LENGTH * 2u) + \
								(VERTICAL_WALL_LENGTH * 2u) + \
								(SNAKE_MAX_LENGTH) + \
								(SNAKE_MAX_FOOD_ITEMS))

#define SNAKE_SPEED_Y_FACTOR ((GRAPHICS_Y_SIZE) / 10u)
#define SNAKE_SPEED_X_FACTOR ((GRAPHICS_X_SIZE) / 10u)

#define SNAKE_TICK_CYCLE (10000u)

#define SNAKE_FOOD_ADD_CYCLE    (50u)
#define SNAKE_FOOD_REMOVE_CYCLE (100u)

#define SNAKE_UP    (65u)
#define SNAKE_DOWN  (66u)
#define SNAKE_LEFT  (68u)
#define SNAKE_RIGHT (67u)
#define SNAKE_PAUSE (32u)

#define SNAKE_SCORE_PER_FOOD_ITEM (125u)

typedef struct Snake_
{
	int xPos;
	int yPos;
	unsigned int length;
	unsigned int direction;
	unsigned int graphicsBufStartPos;
} Snake;

typedef struct SnakeFoodItem_
{
	char appearance;
	unsigned int noOfFoodItems;
	unsigned int graphicsBufStartPos;
} SnakeFoodItem;

static GraphicsEntity snakeGraphics[(NUM_GRAPHICAL_ENTITIES)];
static Snake snake;
static unsigned int snakeRunCnt;
static SnakeFoodItem snakeFood = { 'Q', 0u, 0u };
static unsigned int score;
static unsigned char paused;
static unsigned char currKey;

static void handleSnakeKey();
static void renderSnake(void);
static void checkWallCollision(void);
static void generateFoodItem(void);
static void checkFoodCollision(void);
static void checkSnakeCollision(void);
static void removeFoodItem(void);
static void printSnakeScore(void);
static void printSnakeInstructions(void);
static void printSnakeStatus(void);

static void handleSnakeKey()
{
	unsigned char key = getKey();

	if((INPUT_HANDLER_KEY_INVALID) != key)
	{

		if((key == (SNAKE_UP) ||
		   key == (SNAKE_DOWN) ||
		   key == (SNAKE_LEFT) ||
		   key == (SNAKE_RIGHT)) &&
		   0u == paused)
		{
			if(((SNAKE_DOWN) == snake.direction && key != (SNAKE_UP)) ||
			   ((SNAKE_UP) == snake.direction && key != (SNAKE_DOWN)) ||
			   ((SNAKE_RIGHT) == snake.direction && key != (SNAKE_LEFT)) ||
			   ((SNAKE_LEFT) == snake.direction && key != (SNAKE_RIGHT)))
			{
				snake.direction = key;
			}
		}

		currKey = key;
	}

	if(key == (QUIT))
	{
		gameStop();
	}

	if(key == (SNAKE_PAUSE))
	{
		paused = !paused;
	}
}

static void renderSnake(void)
{
	unsigned int snakeBodyIndex = snake.length - 1u;

	for( ; snakeBodyIndex >= 1u; snakeBodyIndex--)
	{
		snakeGraphics[snake.graphicsBufStartPos + snakeBodyIndex] = snakeGraphics[snake.graphicsBufStartPos + snakeBodyIndex - 1u];
		snakeGraphics[snake.graphicsBufStartPos + snakeBodyIndex].appearance = '*';
	}

	if((SNAKE_UP) == snake.direction)
	{
		snake.yPos += -1;
	}

	if((SNAKE_DOWN) == snake.direction)
	{
		snake.yPos += 1;
	}

	if((SNAKE_LEFT) == snake.direction)
	{
		snake.xPos += -1;
	}

	if((SNAKE_RIGHT) == snake.direction)
	{
		snake.xPos += 1;
	}

	snakeGraphics[snake.graphicsBufStartPos].appearance = '@';
	snakeGraphics[snake.graphicsBufStartPos].xPos = snake.xPos;
	snakeGraphics[snake.graphicsBufStartPos].yPos = snake.yPos;
}

static void checkWallCollision(void)
{
	if(snake.xPos <= 0 || snake.xPos >= (int) ((HORIZONTAL_WALL_LENGTH) - 1) ||
	   snake.yPos <= 0 || snake.yPos >= (int) ((VERTICAL_WALL_LENGTH) - 1))
	{
		initSnake();
	}
}

static void generateFoodItem(void)
{
	unsigned int xPos = rand() % ((HORIZONTAL_WALL_LENGTH) - 2u) + 1u;
	unsigned int yPos = rand() % ((VERTICAL_WALL_LENGTH) - 2u) + 1u;

	unsigned int graphicsBufIndex = snakeFood.graphicsBufStartPos;
	unsigned int i = 0u;

	for( ; i < (SNAKE_MAX_FOOD_ITEMS); ++i)
	{
		if(' ' == snakeGraphics[graphicsBufIndex].appearance)
		{
			snakeFood.noOfFoodItems += 1u;
			snakeGraphics[graphicsBufIndex].appearance = snakeFood.appearance;
			snakeGraphics[graphicsBufIndex].xPos = xPos;
			snakeGraphics[graphicsBufIndex].yPos = yPos;
			i = (SNAKE_MAX_FOOD_ITEMS);
		}

		graphicsBufIndex++;
	}
}

static void checkFoodCollision(void)
{
	unsigned int graphicsBufIndex = snakeFood.graphicsBufStartPos;
	unsigned int i = 0u;

	for( ; i < (SNAKE_MAX_FOOD_ITEMS); ++i)
	{
		if(' ' != snakeGraphics[graphicsBufIndex].appearance)
		{
			if(snake.xPos == (int) snakeGraphics[graphicsBufIndex].xPos &&
			   snake.yPos == (int) snakeGraphics[graphicsBufIndex].yPos)
			{
				i = (SNAKE_MAX_FOOD_ITEMS);
				snake.length += 1u;
				snakeFood.noOfFoodItems -= 1u;
				snakeGraphics[graphicsBufIndex].appearance = ' ';
				score += (SNAKE_SCORE_PER_FOOD_ITEM);
			}
		}

		graphicsBufIndex++;
	}
}

static void checkSnakeCollision(void)
{
	unsigned int graphicsBufIndex = snake.graphicsBufStartPos + 1u;
	unsigned int i = 0u;

	for( ; i < (SNAKE_MAX_LENGTH); ++i)
	{
		if('*' == snakeGraphics[graphicsBufIndex].appearance)
		{
			if(snake.xPos == (int) snakeGraphics[graphicsBufIndex].xPos &&
			   snake.yPos == (int) snakeGraphics[graphicsBufIndex].yPos)
			{
				i = (SNAKE_MAX_LENGTH);
				initSnake();
			}
		}

		graphicsBufIndex++;
	}
}

static void removeFoodItem(void)
{
	if(0u != snakeFood.noOfFoodItems)
	{
		unsigned int itemToRemove = rand() % snakeFood.noOfFoodItems;

		unsigned int graphicsBufIndex = snakeFood.graphicsBufStartPos;
		unsigned int i = 0u;
		unsigned int foodItemIndex = 0u;

		for( ; i < (SNAKE_MAX_FOOD_ITEMS); ++i)
		{
			if(' ' != snakeGraphics[graphicsBufIndex].appearance)
			{
				if(foodItemIndex == itemToRemove)
				{
					i = (SNAKE_MAX_FOOD_ITEMS);
					snakeFood.noOfFoodItems -= 1u;
					snakeGraphics[graphicsBufIndex].appearance = ' ';
				}

				foodItemIndex++;
			}

			graphicsBufIndex++;
		}
	}
}

static void printSnakeScore(void)
{
	(void) printf("Score: %u\n", score);
}

static void printSnakeInstructions(void)
{
	printf("Control snake: Arrow keys\nQuit: q\nPause: space\n");
}

static void printSnakeStatus(void)
{
	(void) printf("Last key pressed: %u\nPaused: %u\n", currKey, paused);
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
		snakeGraphics[i].appearance = ' ';
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

	snake.length = 3u;
	snake.xPos = 10;
	snake.yPos = 10;
	snake.direction = (SNAKE_DOWN);

	snake.graphicsBufStartPos = graphicsIndex;

	snakeGraphics[snake.graphicsBufStartPos].appearance = '@';
	snakeGraphics[snake.graphicsBufStartPos].xPos = snake.xPos;
	snakeGraphics[snake.graphicsBufStartPos].yPos = snake.yPos;

	renderSnake();

	snakeFood.graphicsBufStartPos = snake.graphicsBufStartPos + (SNAKE_MAX_LENGTH);
	snakeFood.noOfFoodItems = 0u;

	srand(time(0));

	score = 0u;

	paused = 0u;
}

void snakeRun(void)
{
	if(0u == paused)
	{
		if(((snake.direction == (SNAKE_UP) ||
			snake.direction == (SNAKE_DOWN)) &&
			snakeRunCnt % (SNAKE_SPEED_X_FACTOR) == 0) ||
			((snake.direction == (SNAKE_LEFT) ||
			snake.direction == (SNAKE_RIGHT)) &&
			snakeRunCnt % (SNAKE_SPEED_Y_FACTOR) == 0))
		{
			handleSnakeKey();
			renderSnake();
			termGraphicsDraw(snakeGraphics, (NUM_GRAPHICAL_ENTITIES));
			printSnakeScore();
			printSnakeInstructions();
			printSnakeStatus();
			checkWallCollision();
			checkFoodCollision();
			checkSnakeCollision();
		}

		if(snakeRunCnt % (SNAKE_FOOD_ADD_CYCLE) == 0u)
		{
			generateFoodItem();
		}

		if(snakeRunCnt % (SNAKE_FOOD_REMOVE_CYCLE) == 0u)
		{
			removeFoodItem();
		}

		snakeRunCnt = (snakeRunCnt + 1u) % (SNAKE_TICK_CYCLE);
	}
	else
	{
		handleSnakeKey();
		termGraphicsDraw(snakeGraphics, (NUM_GRAPHICAL_ENTITIES));
		printSnakeScore();
		printSnakeInstructions();
		printSnakeStatus();
	}
}
