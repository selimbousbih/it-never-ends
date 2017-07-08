#ifndef OBJECTS_H
#define OBJECTS_H
#include "items.h"
#include "bullet.h"

typedef struct Dialogue
{
	int interrupt ;
	int saving_state;
	int choice;
	SDL_Surface *choicy;
	SDL_Surface *dialogue;
	SDL_Surface *btnYes;
	SDL_Surface *btnNo;
	SDL_Surface *saveYESa;
	SDL_Surface *saveYESb;
	SDL_Surface *saveNOa;
	SDL_Surface *saveNOb;

	SDL_Rect positionChoice;
	SDL_Rect positionD;
	SDL_Rect positionYES;
	SDL_Rect positionNO;
}Dialogue;

typedef struct Texte
{
SDL_Surface *texte;
SDL_Rect position;
TTF_Font *police;
SDL_Color couleur;
FILE *f;
int actuel,i,fix,line, indice[26];

char ch[6], aux[100], dialogue[26][100];
char message[100];

char text_quote[60];
SDL_Surface *quote;
SDL_Rect pos_quote;

}Texte;

typedef struct Particle
{
    SDL_Surface *image;
	SDL_Rect pos_src, position, relativePos;
	Cercle cercle;
}Particle;

typedef struct Borders
{
    int left[6], right[6];
}Borders;

typedef struct Objects
{
	Bullet bullet[5];
	unsigned int elapsed;

    Particle objective;
    Borders borders;
    Cercle door[12];
	Inventory inventory;
	SDL_Surface *tutorial[10];
	SDL_Rect pos_tuto;

}Objects;


#endif
