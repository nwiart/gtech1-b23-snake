#include "Renderer.h"

#include "Texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
using namespace std;



Renderer::Renderer()
	: window( 0 ), renderer( 0 ), closeRequested( false )
{
	
}

Renderer::~Renderer()
{
	if ( renderer ) SDL_DestroyRenderer( renderer );
	if ( window ) SDL_DestroyWindow( window );

	SDL_Quit();
}

bool Renderer::initialize( int width, int height, int frameDelay )
{
	this->frameDelay = frameDelay;

	// SDL init.
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "SDL init failed : " << SDL_GetError() << endl;
		return false;
	}

	// SDL window.
	window = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_SHOWN );

	if ( !window )
	{
		cout << "SDL window creation failed : " << SDL_GetError() << endl;
		return false;
	}

	// SDL renderer.
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	// Image loading.
	IMG_Init( IMG_INIT_PNG );

	return true;
}

void Renderer::beginRender()
{
	SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( this->renderer );
}

void Renderer::endRender()
{
	SDL_RenderPresent( this->renderer );
}

void Renderer::pollWindowEvents()
{
	// Process all events.
	SDL_Event e;
	while ( SDL_PollEvent(&e) != 0 )
	{
		switch ( e.type )
		{
		case SDL_QUIT:
			closeRequested = true;
			break;

		case SDL_KEYDOWN:
			switch ( e.key.keysym.sym )
			{
			case SDLK_ESCAPE:
				closeRequested = true;
				break;
			}
			break;
		}
	}

	// Delay between frames.
	static Uint32 frameTime, lastFrameTime = 0;
	frameTime = SDL_GetTicks();
	
	if ( (frameTime - lastFrameTime) < frameDelay )
		SDL_Delay( frameDelay - (frameTime - lastFrameTime) );
	lastFrameTime = frameTime;
}

Texture* Renderer::createTexture( const char* path )
{
	SDL_Surface* surface = IMG_Load( path );
	SDL_Texture* texture = SDL_CreateTextureFromSurface( this->renderer, surface );

	SDL_FreeSurface( surface );

	Texture* t = new Texture( texture );
	return t;
}

void Renderer::drawRect( Texture* t, int x, int y, int width, int height, int angle )
{
	SDL_Rect dest = { x, y, width, height };
	SDL_RenderCopyEx( this->renderer, t->texture, 0, &dest, angle, 0, SDL_FLIP_NONE );
}