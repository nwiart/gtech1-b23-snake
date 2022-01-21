#pragma once

class Texture;

struct SDL_Window;
struct SDL_Renderer;

	/// Renderer class managing the SDL window and renderer.
	/// This class also provides methods for rendering colored and textured rectangles.
class Renderer
{
public:

	Renderer();
	~Renderer();

		/// Initializes SDL objects and returns whether the initialization was successful.
	int initialize( int width, int height, const char* title, int frameDelay = 20 );

	void beginRender();
	void endRender();

	void pollWindowEvents();
	bool isCloseRequested() const { return closeRequested; }

		/// Create a texture from an image on disk.
		/// path : path of the image, relative to the working directory.
	Texture* createTexture( const char* path );

	void drawRect( unsigned int color, int x, int y, int width, int height, int angle );
	void drawRect( Texture* t, int x, int y, int width, int height, int angle );



private:

	SDL_Window* window;
	SDL_Renderer* renderer;

		/// Time interval between frames in milliseconds.
	unsigned int frameDelay;

		/// Does the user want to close the window?
	bool closeRequested;
};