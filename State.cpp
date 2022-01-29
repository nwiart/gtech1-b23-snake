#include "State.h"

#include "Renderer.h"

Renderer* State::renderer = 0;

void State::setRenderer( Renderer* r )
{
	if ( !renderer )
		renderer = r;
}

int State::getTileSizeX()
{
	return (renderer->getWindowWidth()) / GRID_SIZE_X;
}
	
int State::getTileSizeY()
{
	return (renderer->getWindowHeight() - 128) / GRID_SIZE_Y;
}