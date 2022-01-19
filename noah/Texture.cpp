#include "Texture.h"

#include <SDL2/SDL.h>

Texture::Texture( SDL_Texture* t )
	: texture( t )
{
	
}

Texture::~Texture()
{
	if ( texture )
		SDL_DestroyTexture( texture );
}