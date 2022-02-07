#include "SnakeRenderer.h"

#include "Renderer.h"
#include "Texture.h"
#include "Snake.h"
#include "State.h"

#include <SDL2/SDL.h>

SnakeRenderer::SnakeRenderer( Renderer* r )
	: renderer( r )
{
	snakeHeadTex = renderer->createTexture( "res/snake_head.png" );
	snakeBodyTex = renderer->createTexture( "res/snake_body.png" );
	snakeTurnTex = renderer->createTexture( "res/snake_turn.png" );
	snakeTailTex = renderer->createTexture( "res/snake_tail.png" );
}

SnakeRenderer::~SnakeRenderer()
{
	renderer->destroyTexture( snakeHeadTex );
	renderer->destroyTexture( snakeBodyTex );
	renderer->destroyTexture( snakeTurnTex );
	renderer->destroyTexture( snakeTailTex );
}

void SnakeRenderer::setAlpha( unsigned char a )
{
	snakeHeadTex->setAlpha( a );
	snakeBodyTex->setAlpha( a );
	snakeTurnTex->setAlpha( a );
	snakeTailTex->setAlpha( a );
}

void SnakeRenderer::render( Snake* snake )
{
	const int tileSizeX = State::getTileSizeX();
	const int tileSizeY = State::getTileSizeY();

	Segment* s = snake->getHead();
	int dir = snake->getDirection();

	while ( s )
	{
		// Get turn.
		int newDir;
		if ( s != snake->getTail() ) {
			if ( s == snake->getHead() ) {
				newDir = dir;
			}
			else {
				newDir = Snake::getDirectionBewteen( s->next, s );
			}
		}

		// Get texture rotation.
		int rotation;
		switch ( newDir )
		{
		case DIRECTION_UP:    rotation = -90; break;
		case DIRECTION_DOWN:  rotation =  90; break;
		case DIRECTION_LEFT:  rotation = 180; break;
		case DIRECTION_RIGHT: rotation =   0; break;
		}

		// Left turn.
		if ( newDir < dir && !(dir == DIRECTION_RIGHT && newDir == DIRECTION_UP) || (dir == DIRECTION_UP && newDir == DIRECTION_RIGHT) )
			rotation += 90;

		// Determine which texture to use.
		Texture* tex;
		if      ( s == snake->getHead() ) tex = snakeHeadTex;
		else if ( s == snake->getTail() ) tex = snakeTailTex;
		else if ( newDir != dir )         tex = snakeTurnTex;
		else                              tex = snakeBodyTex;

		renderer->drawRect( tex, s->posX * tileSizeX, s->posY * tileSizeY + 128, tileSizeX, tileSizeY, rotation );

		s = s->next;
		dir = newDir;
	}
}