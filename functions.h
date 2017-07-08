#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include "game.h"
#include "bullet.h"

int relative_x(GAME *game, SDL_Rect position);
char *tostr(int x);
int random_case(GAME *game);
int center_camera(GAME *game);
void free_memory(GAME *game);
int SDL_TICKS_PASSED(unsigned int A, unsigned int B);
void loading_screen(GAME *game);
void blit_text(GAME *game);
Texte dialogue_lines(Texte texte);
void load_music(GAME *game);
void init_level(GAME *game);
void play_video(GAME *game, char filename[30]);
Color collision_color(GAME *game);

void init_bullet(GAME *game, int a, int b);
void blit_bullet(GAME *game);
void bullet_shot(GAME *game, int a);

void load_menuQuit(GAME *game);

void show_inventory(GAME *game);

#endif // FONCTIONS_H_INCLUDED
