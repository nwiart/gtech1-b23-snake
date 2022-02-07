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

void Texture::setAlpha( unsigned char a )
{
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	SDL_SetTextureAlphaMod( texture, a );
}