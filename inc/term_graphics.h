#ifndef HEADER_TERM_GRAPHICS
#define HEADER_TERM_GRAPHICS

#define GRAPHICS_Y_SIZE (30u)
#define GRAPHICS_X_SIZE (50u)

typedef struct GraphicsEntity_
{
	char appearance;
	unsigned int xPos;
	unsigned int yPos;
} GraphicsEntity;

void termGraphicsInit(void);

void termGraphicsDraw(GraphicsEntity graphics[], unsigned int noOfEntities);

#endif
