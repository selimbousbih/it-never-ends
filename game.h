#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>

#include "declarations.h"
#include "character.h"
#include "objects.h"
#include "collision.h"

#define START_Y (game->config.resolution_h-game->background.image[0]->h)/2
#define TRUE_X (game->background.scroll_x+game->character.position.x)

typedef struct Config
{
	FILE *f;
	int resolution_w, resolution_h;
	int fullscreen;
}Config;


typedef struct Music
{
	Mix_Music *ambient;

}Music;


typedef struct Background
{
    SDL_Surface *image[7];
    SDL_Surface *levelCollision;
    SDL_Rect position, pos_rain;
    int scroll_x;
    int scroll_y;
    int counter;
}Background;

typedef struct Input
{
	int left, right, up, down, enter, fix;
    int startJump, jumpHeight;

}Input;


typedef struct GUI
{
    SDL_Surface *avatar, *hp, *inventaire, *died[33];
    SDL_Surface *dialogue[5], *btn_animated[2];
    SDL_Rect pos_dialogue, pos_btn;
    SDL_Rect pos_avatar, pos_hp, pos_inv;
	SDL_Surface *frame;

    int show_dialogue, show_inv, indice;
}GUI;

typedef struct Global
{
    int elapsed_npc[5], get_elapsed_npc[5];
    int obj_i, EOL; //EOL = end of level
    int fix, animate;
    int show_message;
    int movement;
    int on_door;
    int FIN;
    int fire_i;
	int fix_died, frame_died;
	int level2_show_items;
    int stopDisplay;
    int green_item, blue_item;
    int checkpoint;
    int fix_tutorial;
    int on_tutorial;
}Global;

typedef struct GAME
{
	SDL_Surface *screen;
	Background background;
	Input input, arduino;
	Character character, npc[5];
	Texte texte;
	Objects objects;
    GUI gui;
    Music musique;
    Global global;
    Config config;
    Dialogue dialogue;

	int level, showMenu;
    int sprite;

}GAME;



#endif
