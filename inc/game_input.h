#ifndef HEADER_GAME_INPUT
#define HEADER_GAME_INPUT

#define INPUT_HANDLER_KEY_INVALID (0xFFu)
#define QUIT ('q')
#define CONFIGURE ('c')

void initGameInput(void);

void deInitGameInput(void);

unsigned char getKey(void);

#endif
