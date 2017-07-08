#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

void blit_bullet(GAME *game);
int update_display (void *data);
void getPositions(GAME *game);
void update_screen(GAME *game);
void BlitNPC(GAME *game);
int random_case(GAME *game);
void blit_text(GAME *game);
void show_message(GAME *game);


#endif // DISPLAY_H_INCLUDED
