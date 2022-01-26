#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#define DIRECTION_UP    0
#define DIRECTION_LEFT  1
#define DIRECTION_DOWN  2
#define DIRECTION_RIGHT 3


class Segment
{
public:

	Segment( int x, int y );

public:

	int posX;
	int posY;

	Segment* next;
};


class Snake
{
public:

	Snake();
	~Snake();

	void move();

	Segment* getHead() const;
	Segment* getTail() const;

	int getHeadPosX() const;
	int getHeadPosY() const;

	int getDirection() const;
	void setDirection( int dir );

	static int getDirectionBewteen( Segment* s0, Segment* s1 );

public:

	void addSegment();

private:

	Segment* head;
	Segment* tail;
	int direction;
};


#endif // SNAKE_SNAKE_H