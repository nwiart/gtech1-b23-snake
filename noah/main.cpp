#include "Renderer.h"

#include <SDL2/SDL.h>

// Game renderer.
Renderer* renderer = 0;



int main()
{
	// Initialize renderer with window 640x640.
	renderer = new Renderer();
	if ( !renderer->initialize( 1024, 768 ) )
	{
		return 1;
	}

	Texture* backgroundTex = renderer->createTexture( "res/background.png" );
	Texture* terrainTex    = renderer->createTexture( "res/terrain.png" );
	Texture* fruitTex      = renderer->createTexture( "res/fruit.png" );



	// Main game loop.
	int dir = 0, x = 0, y = 0;
	int movementTimer = 25;
	while ( !renderer->isCloseRequested() )
	{
		// Game logic.
		const Uint8* keyStates = SDL_GetKeyboardState( NULL );
		if ( keyStates[SDL_SCANCODE_UP] )     dir = 0;
		if ( keyStates[SDL_SCANCODE_DOWN] )   dir = 1;
		if ( keyStates[SDL_SCANCODE_LEFT] )   dir = 2;
		if ( keyStates[SDL_SCANCODE_RIGHT] )  dir = 3;

		movementTimer--;
		if ( movementTimer == 0 )
		{
			movementTimer = 25;

			if ( dir == 0 && y != 0 )  y -= 1;
			if ( dir == 1 && y != 9 )  y += 1;
			if ( dir == 2 && x != 0 )  x -= 1;
			if ( dir == 3 && x != 15 ) x += 1;
		}
		


		// Rendering.
		renderer->beginRender();

		// Render background (sky & trees).
		renderer->drawRect( 0x0080FFFF, 0, 0,  1024, 64, 0 );
		renderer->drawRect( 0x806020FF, 0, 64, 1024, 64, 0 );
		for ( int i = 0; i < 8; ++i ) {
			renderer->drawRect( backgroundTex, i * 128, 0, 128, 128, 0 );
		}

		// Render grid terrain.
		for ( int x = 0; x < 16; ++x ) {
			for ( int y = 0; y < 10; ++y ) {
				renderer->drawRect( terrainTex, x * 64, y * 64 + 128, 64, 64, 0 );
			}
		}

		// Just a sample fruit.
		renderer->drawRect( fruitTex, x * 64, y * 64 + 128, 64, 64, 0 );
		
		renderer->endRender();
		renderer->pollWindowEvents();
	}



	delete renderer;
	return 0;
}