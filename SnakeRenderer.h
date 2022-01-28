#ifndef SNAKE_SNAKE_RENDERER_H
#define SNAKE_SNAKE_RENDERER_H

class Snake;

class Renderer;
class Texture;

	/// This class manages the snake's textures and the snake rendering process.
class SnakeRenderer
{
public:

	SnakeRenderer( Renderer* r );
	~SnakeRenderer();

		/// Renders the specified snake using a renderer.
	void render( Snake* s );

private:

	Renderer* renderer;

	Texture* snakeHeadTex;
	Texture* snakeBodyTex;
	Texture* snakeTurnTex;
	Texture* snakeTailTex;
};

#endif // SNAKE_SNAKE_RENDERER_H