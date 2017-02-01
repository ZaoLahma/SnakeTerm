#ifndef HEADER_GAME_INPUT_HANDLER
#define HEADER_GAME_INPUT_HANDLER

#include "./thread_pool.h"

#define INPUT_HANDLER_KEY_INVALID (0xFF)

void initInputHandler(struct ThreadContext* threadContext);

char getKey(void);

#endif
