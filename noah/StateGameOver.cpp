#include "State.h"

#include "Renderer.h"
#include "Texture.h"

#include <SDL2/SDL.h>


StateGameOver::StateGameOver( Renderer* r, int score, int length )
	: State( r ), score( score ), length( length )
{
	snakeGameOverTex = renderer->createTexture( "res/snake_gameover.png" );
	gameOverTextTex = renderer->createTexture( "res/gameover_text.png" );
	gameOverScoresTex = renderer->createTexture( "res/gameover_scores.png" );
	gameOverInstructionsTex = renderer->createTexture( "res/gameover_instructions.png" );
}

StateGameOver::~StateGameOver()
{
	renderer->destroyTexture( snakeGameOverTex );
	renderer->destroyTexture( gameOverTextTex );
	renderer->destroyTexture( gameOverScoresTex );
	renderer->destroyTexture( gameOverInstructionsTex );
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
	renderer->drawRect( snakeGameOverTex, (renderer->getWindowWidth() - 256) / 2, (renderer->getWindowHeight() - 256) / 2 + 80, 256, 256, 0 );

	// Game over text and instructions.
	renderer->drawRect( gameOverTextTex, (renderer->getWindowWidth() - 400) / 2, 60, 400, 100, 0 );
	renderer->drawRect( gameOverScoresTex, (renderer->getWindowWidth() - 160) / 2 - 90, 180, 160, 80, 0 );
	renderer->drawRect( gameOverInstructionsTex, (renderer->getWindowWidth() - 400) / 2, 620, 400, 100, 0 );

	// Score numbers.
	renderer->drawNumber( score, renderer->getWindowWidth() / 2, 175 );
	renderer->drawNumber( length, renderer->getWindowWidth() / 2, 205 );
	renderer->drawNumber( 0, renderer->getWindowWidth() / 2, 235 );
}