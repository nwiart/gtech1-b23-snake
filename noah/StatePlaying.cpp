#include "State.h"

#include "Snake.h"

#include "Renderer.h"
#include "SnakeRenderer.h"

#include <SDL2/SDL.h>


StatePlaying::StatePlaying( Renderer* r )
	: State( r ), score( 0 ), movementTimer( 5 ), deadTimer( 100 ), dead( false ), snakeRenderer( 0 )
{
	this->snake = new Snake( 5, 10 );
	this->direction = snake->getDirection();

	this->snakeRenderer = new SnakeRenderer( r );
}

StatePlaying::~StatePlaying()
{
	delete this->snake;
	delete this->snakeRenderer;
}

State* StatePlaying::update()
{
	const Uint8* keyStates = SDL_GetKeyboardState( NULL );
	if ( keyStates[SDL_SCANCODE_UP]    && snake->getDirection() != DIRECTION_DOWN )  direction = DIRECTION_UP;
	if ( keyStates[SDL_SCANCODE_DOWN]  && snake->getDirection() != DIRECTION_UP )    direction = DIRECTION_DOWN;
	if ( keyStates[SDL_SCANCODE_LEFT]  && snake->getDirection() != DIRECTION_RIGHT ) direction = DIRECTION_LEFT;
	if ( keyStates[SDL_SCANCODE_RIGHT] && snake->getDirection() != DIRECTION_LEFT )  direction = DIRECTION_RIGHT;

	movementTimer--;
	if ( movementTimer == 0 )
	{
		movementTimer = 5;

		if (keyStates[SDL_SCANCODE_W]) snake->addSegment();

		if ( !dead )
		{
			snake->setDirection( direction );
			snake->move();

			score += 10;

			if ( snake->collides() )
			{
				dead = true;
			}
		}
	}

	// Dead timer before showing game over screen.
	if ( dead ) {
		deadTimer--;

		if ( deadTimer == 0 ) {
			return new StateGameOver( this->renderer, this->score, this->snake->getLength() );
		}
	}

	return 0;
}

void StatePlaying::render()
{
	// Render snake (and blink when dead).
	if ( !dead || (SDL_GetTicks() % 240) >= 120 )
		snakeRenderer->render( snake );

	// Render score.
	renderer->drawRect( 0x604020FF, 15, 15, 5 * 3 * 5 + 4 * 5 + 10, 35, 0 );
	renderer->drawNumber( score, 20, 20 );
}