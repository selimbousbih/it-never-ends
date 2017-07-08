#ifndef ITEMS_H
#define ITEMS_H

typedef struct Item
{
int number;
SDL_Surface *image, *description;
SDL_Rect position, blit_pos;
Cercle cercle;
int have, selected, disposable;
}Item;

typedef struct Inventory
{
int count;
Item item[MAX_ITEMS];

}Inventory;

#endif
