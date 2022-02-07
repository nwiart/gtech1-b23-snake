#include "State.h"

#include "Snake.h"

#include "Renderer.h"
#include "SnakeRenderer.h"

#include <SDL2/SDL.h>
#include "Fruit.hpp"
#include "Utils.h"

#include <iostream>


StatePlaying::StatePlaying()
	: score( 0 ), milliseconds( 0 ), movementTimer( 5 ), deadTimer( 100 ), dead( false ), snakeRenderer( 0 )
{
	if ( !renderer ) {
		std::cout << "You haven't set a renderer in the State class. Specify a valid one before creating a State object.\n";
		return;
	}

	this->snake = new Snake( 5, 10 );
	this->direction = snake->getDirection();

	this->snakeRenderer = new SnakeRenderer( State::renderer );
	
	Fruits[0] = new Fruit(Fruit::GOOD,0,0);
    Fruits[1] = new Fruit(Fruit::BAD,0,0);
	Fruits[2] = new Fruit(Fruit::GHOST,0,0);

	Fruits[1]->active = false;
	Fruits[2]->active = false;

	fruit_set(Fruits[0]);
	fruit_set(Fruits[1]);
	fruit_set(Fruits[2]);

	GoodFruitTex = State::renderer->createTexture("res/fruit.png");
	BadFruitTex = State::renderer->createTexture("res/fruit_bad.png");
}

StatePlaying::~StatePlaying()
{
	delete this->snake;
	delete this->snakeRenderer;

	for ( int i = 0; i < 3; ++i )
		delete Fruits[i];
}

State* StatePlaying::update()
{
	static int lasttime = 0;

	const Uint8* keyStates = SDL_GetKeyboardState( NULL );
	if ( keyStates[SDL_SCANCODE_UP]    && snake->getDirection() != DIRECTION_DOWN )  direction = DIRECTION_UP;
	if ( keyStates[SDL_SCANCODE_DOWN]  && snake->getDirection() != DIRECTION_UP )    direction = DIRECTION_DOWN;
	if ( keyStates[SDL_SCANCODE_LEFT]  && snake->getDirection() != DIRECTION_RIGHT ) direction = DIRECTION_LEFT;
	if ( keyStates[SDL_SCANCODE_RIGHT] && snake->getDirection() != DIRECTION_LEFT )  direction = DIRECTION_RIGHT;

	movementTimer--;
	if ( movementTimer == 0 )
	{
		movementTimer = 5;

		if ( !dead )
		{
			// Update snake position and move by one.
			snake->setDirection( direction );
			snake->move();

			if ( !snake->isGhost() )
			{
				snakeRenderer->setAlpha( 255 );
			}

			// Is snake over a fruit.
			for ( int i = 0; i < 3; ++i )
			{
				Fruit* f = Fruits[i];

				if ( f->active && (snake->getHeadPosX() == f->x && snake->getHeadPosY() == f->y) )
				{
					switch ( f->type )
					{
					case Fruit::GOOD:
						score += 10;
						snake->addSegment();
						break;

					case Fruit::BAD:
						score -= 10;
						snake->removeSegment();
						break;

					case Fruit::GHOST:
						snake->setGhost( true );
						snakeRenderer->setAlpha( 127 );
						break;
					}

					// Randomly replace fruits.
					fruit_set(Fruits[0]);
					fruit_set(Fruits[1]);
					fruit_set(Fruits[2]);

					Fruits[1]->active = (score >= 50);
					Fruits[2]->active = ((rand() % 5) == 0);

					continue;
				}
			}

			// Is snake colliding with itself or with the walls.
			bool collides = snake->collides();
			collides = collides || snake->getHeadPosX() < 0;
			collides = collides || snake->getHeadPosY() < 0;
			collides = collides || snake->getHeadPosX() >= State::GRID_SIZE_X;
			collides = collides || snake->getHeadPosY() >= State::GRID_SIZE_Y;
			if ( collides )
			{
				dead = true;
			}
		}
	}

	// Dead timer before showing game over screen.
	if ( dead ) {
		deadTimer--;

		if ( deadTimer == 0 ) {
			return new StateGameOver( this->score, this->snake->getLength() );
		}
	}

	int time = SDL_GetTicks();
	milliseconds += (time - lasttime);
	lasttime = time;

	return 0;
}

void StatePlaying::fruit_set(Fruit* f)
{
    int posx_fruit = Utils::randomInt( 0, State::GRID_SIZE_X );
    int posy_fruit = Utils::randomInt( 0, State::GRID_SIZE_Y ); 

    Segment* s = snake->getHead();

    while (s)
    {

        if (s->posX == posx_fruit && s->posY == posy_fruit)
        { 
            posx_fruit = Utils::randomInt( 0, this->GRID_SIZE_X );
            posy_fruit = Utils::randomInt( 0, this->GRID_SIZE_Y ); 
            s = snake->getHead();

            continue;
        }
        s = s->next;
    }
    f->x = posx_fruit;
    f->y = posy_fruit;
}

void StatePlaying::render()
{
	// Render snake (and blink when dead).
	if ( !dead || (SDL_GetTicks() % 240) >= 120 )
		snakeRenderer->render( snake );
	
	// Render both fruits.
	const int tileSizeX = State::getTileSizeX();
	const int tileSizeY = State::getTileSizeY();
	float fruitRotation = sin(SDL_GetTicks() / 1000.0F * 3.0F) * 30.0F;

	renderer->drawRect(GoodFruitTex, Fruits[0]->x * tileSizeX, Fruits[0]->y * tileSizeY + 128, tileSizeX, tileSizeY, fruitRotation);
	if (Fruits[1]->active)
		renderer->drawRect(BadFruitTex, Fruits[1]->x * tileSizeX, Fruits[1]->y * tileSizeY + 128, tileSizeX, tileSizeY, fruitRotation);
	if (Fruits[2]->active)
		renderer->drawRect(BadFruitTex, Fruits[2]->x * tileSizeX, Fruits[2]->y * tileSizeY + 128, tileSizeX, tileSizeY, fruitRotation + 180);

	// Render score.
	renderer->drawRect( 0x604020FF, 15, 15, 5 * 3 * 5 + 4 * 5 + 10, 35, 0 );
	renderer->drawNumber( score, 20, 20 );
}