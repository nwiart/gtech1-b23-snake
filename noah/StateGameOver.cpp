#include "State.h"

#include "Renderer.h"
#include "Texture.h"

#include <SDL2/SDL.h>


StateGameOver::StateGameOver( Renderer* r )
	: State( r )
{
	snakeGameOverTex = renderer->createTexture( "res/snake_gameover.png" );
	gameOverTextTex = renderer->createTexture( "res/gameover_text.png" );
	gameOverInstructionsTex = renderer->createTexture( "res/gameover_instructions.png" );
}

State* StateGameOver::update()
{
	const Uint8* keyStates = SDL_GetKeyboardState( 0 );
	if ( keyStates[SDL_SCANCODE_RETURN] )
	{
		return new StatePlaying( this->renderer );
	}

	return 0;
}

void StateGameOver::render()
{
	// Render background.
	renderer->drawRect( 0x604020FF, (renderer->getWindowWidth() - 550) / 2, (renderer->getWindowHeight() - 700) / 2, 550, 700, 0 );

	// Snake image.
	renderer->drawRect( snakeGameOverTex, (renderer->getWindowWidth() - 256) / 2, (renderer->getWindowHeight() - 256) / 2, 256, 256, 0 );

	// Game over text and instructions.
	renderer->drawRect( gameOverTextTex, (renderer->getWindowWidth() - 400) / 2, 60, 400, 100, 0 );
	renderer->drawRect( gameOverInstructionsTex, (renderer->getWindowWidth() - 400) / 2, 620, 400, 100, 0 );
}