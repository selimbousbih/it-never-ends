#ifndef CHAR_H_INCLUDED
#define CHAR_H_INCLUDED
#include "collision.h"
#include "enum.h"


typedef struct Character
{
    SDL_Surface *image;
    SDL_Rect position, src_pos, relativePos;
    Cercle pos_cercle;
    int look, actuel;
    int life, died;
    int elapsed;
    /* Npc vars */
    int vision_range, direction, speed, fix;
    Behavior behavior;
}Character;

#endif // CHAR_H_INCLUDED
