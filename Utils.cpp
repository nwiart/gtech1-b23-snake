#include "Utils.h"

#include <stdlib.h>

int Utils::randomInt( int min, int max )
{
	return (rand() % (max - min)) + min;
}