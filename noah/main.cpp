#include "Renderer.h"

#include <SDL2/SDL.h>

Renderer* renderer = 0;



int main()
{
	// Initialize renderer with window 640x640.
	renderer = new Renderer();
	if ( !renderer->initialize( 640, 640 ) )
	{
		return 1;
	}

	Texture* tex = renderer->createTexture( "res/fruit.png" );

	float x = 0;
	while ( !renderer->isCloseRequested() )
	{
		renderer->beginRender();
		renderer->drawRect( tex, x, 0, 32, 32, 90 );
		renderer->endRender();

		x += 0.5F;

		renderer->pollWindowEvents();
	}

	delete renderer;

	return 0;
}