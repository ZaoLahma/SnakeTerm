#include "../inc/game_snake.h"
#include "../inc/game_schd.h"
#include "../inc/game_param.h"
#include "../inc/game_term_graphics.h"
#include "../inc/game_state.h"
#include "../inc/game_input.h"
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

#define SNAKE_TICK_CYCLE (201u)

#define SNAKE_FOOD_ADD_CYCLE    (20u)
#define SNAKE_FOOD_REMOVE_CYCLE (100u)

#define SNAKE_PAUSE (32u)

#define SNAKE_START_LENGTH (3u)
#define SNAKE_START_X_POS  ((HORIZONTAL_WALL_LENGTH) / 2)
#define SNAKE_START_Y_POS  (1)

#define SNAKE_SCORE_PER_FOOD_ITEM (125u)

#define SNAKE_HEAD_APPEARANCE ('@')
#define SNAKE_BODY_APPEARANCE ('*')
#define SNAKE_FOOD_APPEARANCE ('O')

#define SNAKE_SCORE_TEXT       ("Score: %u | High score: %u\n\n")
#define SNAKE_INSTR_TEXT       ("Configure game: c\nQuit: q\nPause: space\n")
#define SNAKE_KEY_PRESSED_TEXT ("Last key pressed: %u\n")
#define SNAKE_GAME_OVER_TEXT   ("Game over. ")
#define SNAKE_PAUSED_TEXT      ("Game is paused. ")
#define SNAKE_START_TEXT       ("Press space to start\n")
#define SNAKE_CPU_UTIL_TEXT    ("CPU load: %.3f%% (max load: %.3f%%)\n\n")

#define SNAKE_GAME_OVER_ATE_SELF ("Snake ate self!")
#define SNAKE_GAME_OVER_ATE_WALL ("Snake ate wall!")

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
	unsigned int noOfFoodItems;
	unsigned int graphicsBufStartPos;
	char appearance;
} SnakeFoodItem;

static GraphicsEntity snakeGraphics[(NUM_GRAPHICAL_ENTITIES)];
static Snake snake;
static SnakeFoodItem snakeFood;
static unsigned int score;
static unsigned char snakeRunCnt;
static unsigned char paused;
static unsigned char gameOver;
static unsigned char currKey;
static unsigned char SNAKE_UP;
static unsigned char SNAKE_DOWN;
static unsigned char SNAKE_LEFT;
static unsigned char SNAKE_RIGHT;

static char* gameOverReason;

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
		gameOver = 0u;
		gameOverReason = 0u;
	}

	if(key == (CONFIGURE))
	{
		setGameState(GAME_CONFIGURE_RUNNING);
	}
}

static void renderSnake(void)
{
	unsigned int snakeBodyIndex = snake.length - 1u;

	for( ; snakeBodyIndex >= 1u; snakeBodyIndex--)
	{
		snakeGraphics[snake.graphicsBufStartPos + snakeBodyIndex] = snakeGraphics[snake.graphicsBufStartPos + snakeBodyIndex - 1u];
		snakeGraphics[snake.graphicsBufStartPos + snakeBodyIndex].appearance = (SNAKE_BODY_APPEARANCE);
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

	snakeGraphics[snake.graphicsBufStartPos].appearance = (SNAKE_HEAD_APPEARANCE);
	snakeGraphics[snake.graphicsBufStartPos].xPos = snake.xPos;
	snakeGraphics[snake.graphicsBufStartPos].yPos = snake.yPos;
}

static void checkWallCollision(void)
{
	if(snake.xPos <= 0 || snake.xPos >= (int) ((HORIZONTAL_WALL_LENGTH) - 1) ||
	   snake.yPos <= 0 || snake.yPos >= (int) ((VERTICAL_WALL_LENGTH) - 1))
	{
		initSnake();
		gameOver = 1u;
		gameOverReason = (SNAKE_GAME_OVER_ATE_WALL);
	}
}

static void generateFoodItem(void)
{
	if((SNAKE_MAX_FOOD_ITEMS) > snakeFood.noOfFoodItems)
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
}

static void checkFoodCollision(void)
{
	if(0u < snakeFood.noOfFoodItems)
	{
		unsigned int graphicsBufIndex = snakeFood.graphicsBufStartPos;
		unsigned int i = 0u;

		for( ; i < (SNAKE_MAX_FOOD_ITEMS); ++i)
		{
			if(snakeFood.appearance == snakeGraphics[graphicsBufIndex].appearance)
			{
				if(snake.xPos == (int) snakeGraphics[graphicsBufIndex].xPos &&
				   snake.yPos == (int) snakeGraphics[graphicsBufIndex].yPos)
				{
					i = (SNAKE_MAX_FOOD_ITEMS);
					snake.length += 1u;
					snakeFood.noOfFoodItems -= 1u;
					snakeGraphics[graphicsBufIndex].appearance = ' ';
					score += (SNAKE_SCORE_PER_FOOD_ITEM);
					unsigned int highScore;
					getGameParam(GAME_PARAM_HIGH_SCORE, &highScore);
					if(score > highScore)
					{
						(void) setGameParam(GAME_PARAM_HIGH_SCORE, score);
					}
				}
			}

			graphicsBufIndex++;
		}
	}
}

static void checkSnakeCollision(void)
{
	unsigned int graphicsBufIndex = snake.graphicsBufStartPos + 1u;
	unsigned int i = 0u;

	for( ; i < (SNAKE_MAX_LENGTH); ++i)
	{
		if((SNAKE_BODY_APPEARANCE) == snakeGraphics[graphicsBufIndex].appearance)
		{
			if(snake.xPos == (int) snakeGraphics[graphicsBufIndex].xPos &&
			   snake.yPos == (int) snakeGraphics[graphicsBufIndex].yPos)
			{
				i = (SNAKE_MAX_LENGTH);
				initSnake();
				gameOver = 1u;
				gameOverReason = (SNAKE_GAME_OVER_ATE_SELF);
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
			if(snakeFood.appearance == snakeGraphics[graphicsBufIndex].appearance)
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
	const unsigned int numSpaces = ((GRAPHICS_X_SIZE) / 2u) -
			                        (strlen((SNAKE_SCORE_TEXT)) / 2u);
	unsigned int i = 0u;

	for( ; i < numSpaces; ++i)
	{
		(void) printf(" ");
	}

	unsigned int highScore;
	(void) getGameParam(GAME_PARAM_HIGH_SCORE, &highScore);
	(void) printf((SNAKE_SCORE_TEXT), score, highScore);
}

static void printSnakeInstructions(void)
{
	printf((SNAKE_INSTR_TEXT));
}

static void printSnakeStatus(void)
{
	(void) printf((SNAKE_KEY_PRESSED_TEXT), currKey);
	(void) printf((SNAKE_CPU_UTIL_TEXT), getCpuLoadPercentage(), getCpuLoadMaxPercentage());
	if(1u == paused || 1u == gameOver)
	{
		if(1u == gameOver)
		{
			(void) printf((SNAKE_GAME_OVER_TEXT));
			if(0u != gameOverReason)
			{
				(void) printf("%s", gameOverReason);
			}
			(void) printf("\n");
		}
		else
		{
			(void) printf((SNAKE_PAUSED_TEXT));
		}

		(void) printf((SNAKE_START_TEXT));
	}
}

void initSnake(void)
{
	termGraphicsInit();

	getGameParam(GAME_PARAM_UP_KEY, (unsigned int*)&SNAKE_UP);
	getGameParam(GAME_PARAM_DOWN_KEY, (unsigned int*)&SNAKE_DOWN);
	getGameParam(GAME_PARAM_LEFT_KEY, (unsigned int*)&SNAKE_LEFT);
	getGameParam(GAME_PARAM_RIGHT_KEY, (unsigned int*)&SNAKE_RIGHT);

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

	snake.length =    (SNAKE_START_LENGTH);
	snake.xPos =      (SNAKE_START_X_POS);
	snake.yPos =      (SNAKE_START_Y_POS);
	snake.direction = (SNAKE_DOWN);

	snake.graphicsBufStartPos = graphicsIndex;

	snakeGraphics[snake.graphicsBufStartPos].appearance = (SNAKE_HEAD_APPEARANCE);
	snakeGraphics[snake.graphicsBufStartPos].xPos = snake.xPos;
	snakeGraphics[snake.graphicsBufStartPos].yPos = snake.yPos;

	renderSnake();

	snakeFood.appearance = (SNAKE_FOOD_APPEARANCE);
	snakeFood.graphicsBufStartPos = snake.graphicsBufStartPos + (SNAKE_MAX_LENGTH);
	snakeFood.noOfFoodItems = 0u;

	srand(time(0));

	score = 0u;

	paused = 1u;

	gameOver = 0u;
	gameOverReason = 0u;

	setGameState(GAME_SNAKE_RUNNING);
}

void snakeRun(void)
{
	if(0u == paused)
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
