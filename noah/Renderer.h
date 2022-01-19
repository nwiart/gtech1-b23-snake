#pragma once

class Texture;

struct SDL_Window;
struct SDL_Renderer;

class Renderer
{
public:

	Renderer();
	~Renderer();

		/// Initializes SDL objects and returns whether the initialization was successful.
	bool initialize( int width, int height, int frameDelay = 20 );

	void beginRender();
	void endRender();

	void pollWindowEvents();
	bool isCloseRequested() const { return closeRequested; }

		/// Create a texture from an image on disk.
		/// path : path of the image, relative to the working directory.
	Texture* createTexture( const char* path );

	void drawRect( Texture* t, int x, int y, int width, int height, int angle );



private:

	SDL_Window* window;
	SDL_Renderer* renderer;

		/// Time interval between frames in milliseconds.
	unsigned int frameDelay;

		/// Does the user want to close the window?
	bool closeRequested;
};