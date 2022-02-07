#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#define DIRECTION_UP    0
#define DIRECTION_LEFT  1
#define DIRECTION_DOWN  2
#define DIRECTION_RIGHT 3


	/// Snake segment. This can represent any segment (head, body, tail...) by its position.
class Segment
{
public:

	Segment( int x, int y );

public:

		/// Segment position in the game's grid.
	int posX;
	int posY;

		/// Linked list pointer.
	Segment* next;
};


	/// Snake.
class Snake
{
public:

		/// Constructor, with initial snake position.
	Snake( int x, int y );
	~Snake();

		/// Moves the snake by one according to the current snake's direction.
		/// This method reuses the tail segment by placing it to the front (as the new head)
		/// and updating its position.
	void move();

		/// Tests if the snake's head collides with another segment.
	bool collides() const;

	Segment* getHead() const;
	Segment* getTail() const;

	int getHeadPosX() const;
	int getHeadPosY() const;

	int getDirection() const;
	void setDirection( int dir );

		/// Compute the snake's length.
	int getLength() const;

		/// "Ghost" mode disables the snake's self collision temporarily.
	bool isGhost() const;
	void setGhost( bool b );

		/// Get the direction from two adjacent segments.
	static int getDirectionBewteen( Segment* s0, Segment* s1 );



public:

		/// Appends a new segment to the snake.
		/// The newly created segment becomes the new tail.
	void addSegment();


	void removeSegment();

		/// Moves the tail segment to the head segment and rearranges the necessary pointers.
		/// This is used by move() to reuse segments instead of deleting and recreating new ones.
	void moveTailToHead();



private:

	Segment* head;
	Segment* tail;

	int direction;

	int ghostTimer;
};


#endif // SNAKE_SNAKE_H