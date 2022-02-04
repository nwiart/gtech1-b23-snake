#include "Snake.h"

#include "Renderer.h"
#include "State.h"

#include <SDL2/SDL.h>

#include <stdlib.h>
#include <time.h>


#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768



// Game renderer.
Renderer* renderer = 0;

void init();
void renderGameOver();



int main()
{
	srand( time( 0 ) );

	// Initialize renderer with window 1024x768
	renderer = new Renderer();
	if ( renderer->initialize( WINDOW_WIDTH, WINDOW_HEIGHT, "Snake Game!", 20 ) )
	{
		return 1;
	}

	Texture* backgroundTex = renderer->createTexture( "res/background.png" );
	Texture* terrainTex    = renderer->createTexture( "res/terrain.png" );

	State::setRenderer( renderer );
	State* state = new StateMainMenu();



	// Main game loop.
	while ( !renderer->isCloseRequested() )
	{
		// Game logic.
		State* newState = state->update();
		


		// Rendering.
		renderer->beginRender();

		// Render background (sky & trees).
		renderer->drawRect( 0x0080FFFF, 0, 0,  1024, 64, 0 );
		renderer->drawRect( 0x806020FF, 0, 64, 1024, 64, 0 );
		for ( int i = 0; i < 8; ++i ) {
			renderer->drawRect( backgroundTex, i * 128, 0, 128, 128, 0 );
		}

		// Render grid terrain.
		const int tileSizeX = State::getTileSizeX();
		const int tileSizeY = State::getTileSizeY();
		for ( int x = 0; x < State::GRID_SIZE_X; ++x ) {
			for ( int y = 0; y < State::GRID_SIZE_Y; ++y ) {
				renderer->drawRect( terrainTex, x * tileSizeX, y * tileSizeY + 128, tileSizeX, tileSizeY, 0 );
			}
		}

		state->render();
		
		renderer->endRender();
		renderer->pollWindowEvents();



		// State switching.
		if ( newState )
		{
			delete state;
			state = newState;
		}
	}



	delete renderer;
	return 0;
}