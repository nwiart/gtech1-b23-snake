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

int Renderer::initialize( int width, int height, const char* title, int frameDelay )
{
	this->frameDelay = frameDelay;

	this->width  = width;
	this->height = height;

	// SDL init.
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "SDL init failed : " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	// SDL window.
	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_SHOWN );

	if ( !window )
	{
		cout << "SDL window creation failed : " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	// SDL renderer.
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	// Image loading.
	IMG_Init( IMG_INIT_PNG );

	return EXIT_SUCCESS;
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
	while ( SDL_PollEvent(&e) )
	{
		if ( e.type == SDL_QUIT )
		{
			closeRequested = true;
		}
		else if ( e.type == SDL_KEYDOWN )
		{
			switch ( e.key.keysym.sym )
			{
			case SDLK_ESCAPE:
				closeRequested = true;
				break;
			}
		}
	}

	// Delay between frames.
	static Uint32 frameTime, lastFrameTime = 0;
	frameTime = SDL_GetTicks();
	
	SDL_Delay( frameDelay );

	/*if ( (frameTime - lastFrameTime) < frameDelay )
		SDL_Delay( frameDelay - (frameTime - lastFrameTime) );
	lastFrameTime = frameTime;*/
}

Texture* Renderer::createTexture( const char* path )
{
	SDL_Surface* surface = IMG_Load( path );
	if ( !surface ) {
		cout << "Failed to load texture \"" << path << "\"." << endl;
		return 0;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface( this->renderer, surface );

	SDL_FreeSurface( surface );

	Texture* t = new Texture( texture );
	return t;
}

void Renderer::destroyTexture( Texture* t )
{
	delete t;
}

#define DECOMPOSE_RGBA( rgba ) (rgba >> 24) & 0xFF, (rgba >> 16) & 0xFF, (rgba >> 8) & 0xFF, rgba & 0xFF

void Renderer::drawRect( unsigned int color, int x, int y, int width, int height, int angle )
{
	SDL_Rect dest = { x, y, width, height };
	SDL_SetRenderDrawColor( this->renderer, DECOMPOSE_RGBA( color ) );
	SDL_RenderFillRect( this->renderer, &dest );
}

void Renderer::drawRect( Texture* t, int x, int y, int width, int height, int angle )
{
	SDL_Rect dest = { x, y, width, height };
	SDL_RenderCopyEx( this->renderer, t->texture, 0, &dest, angle, 0, SDL_FLIP_NONE );
}

int Renderer::getWindowWidth() const
{
	return width;
}

int Renderer::getWindowHeight() const
{
	return height;
}



/// Digit constants. These strings indicate which rectangles in the 3x5 grid should be visible
/// in order to represent a specific decimal digit.
static const char* zero  = "xxxx xx xx xxxx";
static const char* one   = "  x  x  x  x  x";
static const char* two   = "xxx  xxxxx  xxx";
static const char* three = "xxx  xxxx  xxxx";
static const char* four  = "x xx xxxx  x  x";
static const char* five  = "xxxx  xxx  xxxx";
static const char* six   = "xxxx  xxxx xxxx";
static const char* seven = "xxx  x  x  x  x";
static const char* eight = "xxxx xxxxx xxxx";
static const char* nine  = "xxxx xxxx  xxxx";

static const char** digits[] = { &zero, &one, &two, &three, &four, &five, &six, &seven, &eight, &nine };

static const int DIGIT_PIXEL_SIZE = 5;

void Renderer::drawNumber( int number, int x, int y )
{
	int numDigits = 0;
	int n = number;
	while ( n )
	{
		numDigits++;
		n /= 10;
	}

	while ( numDigits )
	{
		numDigits--;

		drawDigit( number % 10, x + numDigits * 4 * DIGIT_PIXEL_SIZE, y );
		number /= 10;
	}
}

void Renderer::drawDigit( int digit, int xp, int yp )
{
	SDL_Rect rect = { 0, 0, DIGIT_PIXEL_SIZE, DIGIT_PIXEL_SIZE };

	/// Loop if overflow to prevent wrong memory access.
	digit = digit % 10;

	for ( int y = 0; y < 5; ++y )
	{
		for ( int x = 0; x < 3; ++x )
		{
			if ( (*(digits[digit]))[y * 3 + x] == 'x' )
			{
				// Draw shadow.
				SDL_SetRenderDrawColor( this->renderer, 0, 0, 0, 255 );
				rect.x = xp + x * DIGIT_PIXEL_SIZE + DIGIT_PIXEL_SIZE;
				rect.y = yp + y * DIGIT_PIXEL_SIZE + DIGIT_PIXEL_SIZE;
				SDL_RenderFillRect( this->renderer, &rect );

				// Draw white square.
				SDL_SetRenderDrawColor( this->renderer, 255, 255, 255, 255 );
				rect.x -= DIGIT_PIXEL_SIZE;
				rect.y -= DIGIT_PIXEL_SIZE;
				SDL_RenderFillRect( this->renderer, &rect );
			}
		}
	}
}