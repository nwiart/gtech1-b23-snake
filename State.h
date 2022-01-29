#ifndef SNAKE_GAMESTATE_H
#define SNAKE_GAMESTATE_H


class Renderer;
class Texture;
class SnakeRenderer;

class Snake;
class Fruit;

class State
{
public:

	State() { }

		/// Update method. This steps the game logic associated with this game state.
		/// Additionally, the method can return a new state for the game to open next.
		/// To keep the current state, return a null pointer.
	virtual State* update() = 0;

		/// The render method. This renders all elements necessary for the game.
	virtual void   render() = 0;

	static void setRenderer( Renderer* r );

		/// Calculate the size of each grid tile, in pixels.
		// NOTE : We subtract 128 to Y because the trees are not part of the grid.
	static int getTileSizeX();
	static int getTileSizeY();



protected:

	static Renderer* renderer;

public:

		/// Grid size constants.
		/// Values are specified in tiles.
	static const int GRID_SIZE_X = 32;
	static const int GRID_SIZE_Y = 20;
};


class StatePlaying : public State
{
public:

	StatePlaying();
	~StatePlaying();

	virtual State* update() override;
	virtual void   render() override;
	void fruit_set(Fruit* f);


private:

	Snake* snake;
	int direction;

	int score;

	int milliseconds;
	int brightness;
	int movementTimer;
	int deadTimer;
	bool dead;
	Fruit* Fruits[2];

	SnakeRenderer* snakeRenderer;

	Texture* GoodFruitTex;
	Texture* BadFruitTex;
};


class StateGameOver : public State
{
public:

	StateGameOver( int score, int length );
	~StateGameOver();

	virtual State* update() override;
	virtual void   render() override;

private:

	Texture* snakeGameOverTex;
	Texture* gameOverTextTex;
	Texture* gameOverScoresTex;
	Texture* gameOverInstructionsTex;

	int score;
	int length;
};





#endif // SNAKE_GAMESTATE_H