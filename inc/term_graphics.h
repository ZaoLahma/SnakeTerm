#ifndef HEADER_TERM_GRAPHICS
#define HEADER_TERM_GRAPHICS

typedef struct GraphicsEntity_
{
	char appearance;
	unsigned int xCoord;
	unsigned int yCoord;
} GraphicsEntity;

void termGraphicsDraw(GraphicsEntity graphics[], unsigned int noOfEntities);

#endif
