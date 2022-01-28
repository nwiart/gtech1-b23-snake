#include "State.h"

#include "Snake.h"

#include "Renderer.h"
#include "SnakeRenderer.h"

#include <SDL2/SDL.h>
#include "Fruit.hpp"
#include "Utils.h"


StatePlaying::StatePlaying( Renderer* r )
	: State( r ), score( 0 ), movementTimer( 5 ), deadTimer( 100 ), dead( false ), snakeRenderer( 0 )
{
	this->snake = new Snake( 5, 10 );
	this->direction = snake->getDirection();

	this->snakeRenderer = new SnakeRenderer( r );
	
	Fruits[0] = new Fruit(Fruit::GOOD,0,0);
    Fruits[1] = new Fruit(Fruit::BAD,0,0);

	fruit_set(Fruits[0]);
	fruit_set(Fruits[1]);

	GoodFruitTex = r->createTexture("res/fruit.png");
	BadFruitTex = r->createTexture("res/fruit_bad.png");
}

StatePlaying::~StatePlaying()
{
	delete this->snake;
	delete this->snakeRenderer;

	delete Fruits[0];
    delete Fruits[1];
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

			if (snake->getHeadPosX() == Fruits[0]->x && snake->getHeadPosY() == Fruits[0]->y)
			{
				fruit_set(Fruits[0]);
				fruit_set(Fruits[1]);
			}


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

void StatePlaying::fruit_set(Fruit* f)
{
    int posx_fruit = Utils::randomInt( 0, 32 );
    int posy_fruit = Utils::randomInt( 0, 20 ); 

    f->x = posx_fruit;
    f->y = posy_fruit;
}

void StatePlaying::render()
{
	// Render snake (and blink when dead).
	if ( !dead || (SDL_GetTicks() % 240) >= 120 )
		snakeRenderer->render( snake );
	
	renderer->drawRect(GoodFruitTex, Fruits[0]->x*32, Fruits[0]->y*32+128, 32 , 32, 0);
	renderer->drawRect(BadFruitTex, Fruits[1]->x*32, Fruits[1]->y*32+128, 32 , 32, 0);

	// Render score.
	renderer->drawRect( 0x604020FF, 15, 15, 5 * 3 * 5 + 4 * 5 + 10, 35, 0 );
	renderer->drawNumber( score, 20, 20 );
}