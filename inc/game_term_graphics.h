#ifndef HEADER_TERM_GRAPHICS
#define HEADER_TERM_GRAPHICS

#define GRAPHICS_Y_SIZE (20u)
#define GRAPHICS_X_SIZE (35u)

typedef struct GraphicsEntity_
{
	unsigned char xPos;
	unsigned char yPos;
	char appearance;
} GraphicsEntity;

void termGraphicsInit(void);

void termGraphicsDraw(GraphicsEntity graphics[], unsigned int noOfEntities);

#endif
