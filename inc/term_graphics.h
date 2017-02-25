#ifndef HEADER_TERM_GRAPHICS
#define HEADER_TERM_GRAPHICS

#define GRAPHICS_Y_SIZE (20)
#define GRAPHICS_X_SIZE (30)

typedef struct GraphicsEntity_
{
	char appearance;
	unsigned int xPos;
	unsigned int yPos;
} GraphicsEntity;

void termGraphicsInit(void);

void termGraphicsDraw(GraphicsEntity graphics[], unsigned int noOfEntities);

#endif
