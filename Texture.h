#ifndef SNAKE_TEXTURE_H
#define SNAKE_TEXTURE_H

struct SDL_Texture;

	/// Wrapper class for using textures with the renderer.
	/// This allows rendering quads with textures to display an image (or a sprite) in the game.
class Texture
{
	friend class Renderer;

private:

	Texture( SDL_Texture* t );
	~Texture();



private:

	SDL_Texture* texture;
};

#endif // SNAKE_TEXTURE_H