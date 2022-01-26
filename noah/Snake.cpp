#include "Snake.h"


Segment::Segment( int x, int y )
	: posX( x ), posY( y ), next( 0 )
{
	
}


Snake::Snake()
{
	this->head = new Segment( 5, 5 );
	this->tail = this->head;
	this->direction = 0;

	this->addSegment();
	this->addSegment();
	this->addSegment();
	this->addSegment();
	this->addSegment();
	this->addSegment();
	this->addSegment();
	this->addSegment();
}

Snake::~Snake()
{
	Segment* s = head;
	while ( s )
	{
		Segment* del = s;
		s = s->next;
		delete del;
	}
}

void Snake::move()
{
	// Find second to last and make it the last.
	Segment* secondLast = this->head;
	while ( secondLast->next != this->tail )
	{
		secondLast = secondLast->next;
	}

	secondLast->next = 0;

	// Set next to last as head.
	this->tail->next = this->head;

	// Make last as head.
	this->tail->posX = this->head->posX;
	this->tail->posY = this->head->posY;
	this->head = this->tail;

	this->tail = secondLast;

	switch ( direction )
	{
	case DIRECTION_UP:    this->head->posY--; break;
	case DIRECTION_DOWN:  this->head->posY++; break;
	case DIRECTION_LEFT:  this->head->posX--; break;
	case DIRECTION_RIGHT: this->head->posX++; break;
	}
}

Segment* Snake::getHead() const
{
	return this->head;
}

Segment* Snake::getTail() const
{
	return this->tail;
}

int Snake::getHeadPosX() const
{
	return this->head->posX;
}

int Snake::getHeadPosY() const
{
	return this->head->posY;
}

int Snake::getDirection() const
{
	return this->direction;
}

void Snake::setDirection( int dir )
{
	this->direction = dir;
}

int Snake::getDirectionBewteen( Segment* s0, Segment* s1 )
{
	if      ( s1->posY < s0->posY ) return DIRECTION_UP;
	else if ( s1->posY > s0->posY ) return DIRECTION_DOWN;
	else if ( s1->posX < s0->posX ) return DIRECTION_LEFT;
	else if ( s1->posX > s0->posX ) return DIRECTION_RIGHT;

	return -1;
}

void Snake::addSegment()
{
	this->tail->next = new Segment( this->tail->posX, this->tail->posY + 1 );
	this->tail = this->tail->next;
}