#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "game.h"

typedef struct Bullet
{
	SDL_Surface *image;
	SDL_Rect  position, relativePos;
	Cercle cercle;
	int speed, started, direction, moving;
	unsigned int ticks, elapsed;
}Bullet;




#endif // BULLET_H_INCLUDED
