#ifndef SNAKE_GAMESTATE_H
#define SNAKE_GAMESTATE_H


class Renderer;
class Texture;
class SnakeRenderer;

class Snake;

class State
{
public:

	State( Renderer* r ) : renderer( r ) { }

		/// Update method. This steps the game logic associated with this game state.
		/// Additionally, the method can return a new state for the game to open next.
		/// To keep the current state, return a null pointer.
	virtual State* update() = 0;

		/// The render method. This renders all elements necessary for the game.
	virtual void   render() = 0;

protected:

	Renderer* renderer;
};


class StatePlaying : public State
{
public:

	StatePlaying( Renderer* r );

	virtual State* update() override;
	virtual void   render() override;

private:

	Snake* snake;
	int direction;

	int score;

	int movementTimer;
	int deadTimer;
	bool dead;

	SnakeRenderer* snakeRenderer;
};


class StateGameOver : public State
{
public:

	StateGameOver( Renderer* r );

	virtual State* update() override;
	virtual void   render() override;

private:

	Texture* snakeGameOverTex;
	Texture* gameOverTextTex;
	Texture* gameOverInstructionsTex;
};


#endif // SNAKE_GAMESTATE_H