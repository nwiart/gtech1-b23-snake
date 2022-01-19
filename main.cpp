#include <SDL2/SDL.h>

#include <iostream>
using namespace std;

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 640



SDL_Window* window = 0;



int main()
{
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "SDL init failed : " << SDL_GetError() << endl;
		return 1;
	}

	window = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN );

	if ( !window )
	{
		cout << "SDL window creation failed." << endl;
		return 2;
	}

	bool closeRequest = false;
	SDL_Event e;
	Uint32 frameStart, frameTime, frameDelay = 20;
	while ( !closeRequest )
	{
		frameStart = SDL_GetTicks();

		while ( SDL_PollEvent(&e) != 0 )
		{
			switch ( e.type )
			{
			case SDL_QUIT:
				closeRequest = true;
				break;

			case SDL_KEYDOWN:
				switch ( e.key.keysym.sym )
				{
				case SDLK_ESCAPE:
					closeRequest = true;
					break;
				}
				break;
			}
		}

		frameTime = SDL_GetTicks() - frameStart;
		if ( frameTime < frameDelay )
		{
			SDL_Delay( frameDelay - frameTime );
		}
	}

	SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}