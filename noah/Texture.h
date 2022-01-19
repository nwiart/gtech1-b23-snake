#pragma once

struct SDL_Texture;

class Texture
{
	friend class Renderer;

private:

	Texture( SDL_Texture* t );
	~Texture();



private:

	SDL_Texture* texture;
};