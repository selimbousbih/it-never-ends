#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

void level1 (GAME *game);
void level2 (GAME *game);
void level3 (GAME *game);
void level4 (GAME *game);

void update_screen(GAME *game);
void getPositions(GAME *game);
void mouvement_level4(GAME *game);
void teleport_next_door(GAME *game);
void movement(GAME *game);
void movement_npc(GAME *game, int n);
int onTexte(GAME *game);
int collision_cercle(Cercle c1, Cercle c2);
void save_level(GAME *game);
void play_music(Music *musique);
void saving_menu(GAME *game, Dialogue dialogue);
int manage_events(GAME *game, SDL_Event *event);


#endif // LEVEL_H_INCLUDED
