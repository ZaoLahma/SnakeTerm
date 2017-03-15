#include "../../inc/game_configure.h"
#include "../../inc/game_input_handler.h"
#include "../../inc/game_param.h"
#include "../../inc/game_state.h"
#include <stdio.h>

typedef enum GameConfigureState_
{
	GAME_CONF_KEY_UP,
	GAME_CONF_KEY_DOWN,
	GAME_CONF_KEY_LEFT,
	GAME_CONF_KEY_RIGHT,
	GAME_CONF_NO_OF_STATES
} GameConfigureState;

static GameConfigureState currState;

void initGameConfigure(void)
{
	currState = GAME_CONF_KEY_UP;
}

void gameConfigureRun(void)
{
	(void) printf("\n\033c");
	(void) printf("Press key for");

	switch(currState)
	{
		case GAME_CONF_KEY_UP:
		{
			(void) printf(" key up ");
		}
		break;

		case GAME_CONF_KEY_DOWN:
		{
			(void) printf(" key down ");
		}
		break;

		case GAME_CONF_KEY_LEFT:
		{
			(void) printf(" key left ");
		}
		break;

		case GAME_CONF_KEY_RIGHT:
		{
			(void) printf(" key right ");
		}
		break;

		default:
		break;
	}

	unsigned char key;
	key = getKey();

	if((INPUT_HANDLER_KEY_INVALID) != key &&
	   (QUIT) != key &&
	   (CONFIGURE) != key)
	{
		switch(currState)
		{
			case GAME_CONF_KEY_UP:
			{
				setGameParam(GAME_PARAM_UP_KEY, key);
				currState = GAME_CONF_KEY_DOWN;
			}
			break;

			case GAME_CONF_KEY_DOWN:
			{
				setGameParam(GAME_PARAM_DOWN_KEY, key);
				currState = GAME_CONF_KEY_LEFT;
			}
			break;

			case GAME_CONF_KEY_LEFT:
			{
				setGameParam(GAME_PARAM_LEFT_KEY, key);
				currState = GAME_CONF_KEY_RIGHT;
			}
			break;

			case GAME_CONF_KEY_RIGHT:
			{
				setGameParam(GAME_PARAM_RIGHT_KEY, key);
				currState = GAME_CONF_KEY_UP;
				setGameState(GAME_SYS_SETUP_COMPLETE);
			}
			break;

			default:
			break;
		}
	}
}
