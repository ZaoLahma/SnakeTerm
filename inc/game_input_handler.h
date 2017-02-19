#ifndef HEADER_GAME_INPUT_HANDLER
#define HEADER_GAME_INPUT_HANDLER

#define INPUT_HANDLER_KEY_INVALID (0xFFu)

void initInputHandler(void);

void* inputHandlerMain(void*);

void stopInputHandler(void);

char getKey(void);

#endif
