#ifndef HEADER_GAME_INPUT_HANDLER
#define HEADER_GAME_INPUT_HANDLER

#define INPUT_HANDLER_KEY_INVALID (0xFFu)
#define QUIT ('q')
#define CONFIGURE ('c')

void initInputHandler(void);

void* inputHandlerMain(void*);

void stopInputHandler(void);

unsigned char getKey(void);

#endif
