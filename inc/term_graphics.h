#ifndef HEADER_TERM_GRAPHICS
#define HEADER_TERM_GRAPHICS

#define GRAPHICS_Y_SIZE (10u)
#define GRAPHICS_X_SIZE (20u)

typedef struct GraphicsEntity_
{
	char appearance;
	unsigned int xPos;
	unsigned int yPos;
} GraphicsEntity;

void termGraphicsInit(void);

void termGraphicsDraw(GraphicsEntity graphics[], unsigned int noOfEntities);

#endif
