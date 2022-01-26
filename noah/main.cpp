#include "Snake.h"

#include "Renderer.h"
#include "SnakeRenderer.h"

#include <SDL2/SDL.h>

#include <stdlib.h>
#include <time.h>

// Game renderer.
Renderer* renderer = 0;



int main()
{
	srand( time( 0 ) );

	// Initialize renderer with window 640x640.
	renderer = new Renderer();
	if ( renderer->initialize( 1024, 768, "Snake Game!" ) )
	{
		return 1;
	}

	SnakeRenderer* snakeRenderer = new SnakeRenderer( renderer );

	Texture* backgroundTex = renderer->createTexture( "res/background.png" );
	Texture* terrainTex    = renderer->createTexture( "res/terrain.png" );

	Snake* snake = new Snake( 5, 5 );



	// Main game loop.
	int movementTimer = 25;
	int direction = snake->getDirection();

	while ( !renderer->isCloseRequested() )
	{
		// Game logic.
		const Uint8* keyStates = SDL_GetKeyboardState( NULL );
		if ( keyStates[SDL_SCANCODE_UP]    && snake->getDirection() != DIRECTION_DOWN )  direction = DIRECTION_UP;
		if ( keyStates[SDL_SCANCODE_DOWN]  && snake->getDirection() != DIRECTION_UP )    direction = DIRECTION_DOWN;
		if ( keyStates[SDL_SCANCODE_LEFT]  && snake->getDirection() != DIRECTION_RIGHT ) direction = DIRECTION_LEFT;
		if ( keyStates[SDL_SCANCODE_RIGHT] && snake->getDirection() != DIRECTION_LEFT )  direction = DIRECTION_RIGHT;

		movementTimer--;
		if ( movementTimer == 0 )
		{
			movementTimer = 25;

			if (keyStates[SDL_SCANCODE_W])
			{
				snake->setDirection( direction );
				snake->move();
			}
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



		snakeRenderer->render( snake );
		
		renderer->endRender();
		renderer->pollWindowEvents();
	}



	delete renderer;
	return 0;
}