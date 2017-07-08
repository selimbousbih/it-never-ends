#include <windows.h>
#include "game.h"

/**

* @file events.c

* @author C Squad

* @version 1.0

* @date May 14, 2016

*/

void load_next_level(GAME *game);
int save_level(GAME *game);
void teleport_next_door(GAME *game);
int pick_item(GAME *game);
void drop_item(GAME *game);
void reload_this_level(GAME *game);

int manage_events(GAME *game, SDL_Event *event)
{
    int continuer=1;

    if (SDL_PollEvent(event))
    {

        if ((*event).type==SDL_QUIT)
        {
            continuer=0;
        }

        else if ((*event).type==SDL_KEYDOWN)
        {
            switch((*event).key.keysym.sym)
            {
            case SDLK_RIGHT:
            {
                game->input.right=1;
                game->input.left=0;
            }
            break;

            case SDLK_LEFT:
            {
                game->input.left=1;
                game->input.right=0;
            }
            break;

            case SDLK_UP:
            {
                game->input.up=1;
            }
            break;

            case SDLK_e:
            {
                game->gui.show_inv=1;
            }
            break;



            case SDLK_RETURN:
            {
                game->input.enter=1;
                if (game->character.died)
                {
                    game->character.died=0;
                    game->global.fix_died=0;
                    game->background.scroll_x=game->global.checkpoint;
                    game->character.position.x=game->config.resolution_w/2;
                    if (game->character.life<0)
                        {
                            game->character.life=3;
                            game->global.checkpoint=0;
                        }

                }

            }
            break;

            case SDLK_SPACE:
                if (game->gui.show_dialogue)
                {
                    if(game->global.fix==1)
                    {
                        if (game->texte.i<game->texte.line-game->texte.line/2-2)
                            game->texte.i+=2;
                        else
                        {
                            game->gui.show_dialogue=0;
                        }
                        game->global.fix=2;
                    }
                }

                break;

            default:
                break;
            }
        }

        else if((*event).type==SDL_KEYUP)
            switch((*event).key.keysym.sym)
            {
            case SDLK_ESCAPE:
                if (game->global.stopDisplay==0)
                {
                    game->global.stopDisplay=1;
                    game->dialogue.interrupt = 1;
                    game->dialogue.saving_state = 1;
                }
                else
                {
                    game->global.stopDisplay=0;
                    game->dialogue.interrupt = 0;
                    game->dialogue.saving_state = 0;
                }

                break;

            case SDLK_RIGHT:
            {
                game->dialogue.saving_state = 2;
                game->input.right=0;
            }
            break;

            case SDLK_LEFT:
            {
                game->dialogue.saving_state = 1;
                game->input.left=0;
            }
            break;

            case SDLK_UP:
            {
                game->input.up=0;
            }
            break;

            case SDLK_e:
                game->gui.show_inv=0;
                break;


            case SDLK_SPACE:
                if (game->gui.show_dialogue)
                    game->global.fix=1;
                break;
            case SDLK_F10:
                load_next_level(game);
                break;
            case SDLK_r:
                reload_this_level(game);
                break;
            case SDLK_RETURN:
                if (game->dialogue.interrupt==1)
                {
                    if (game->dialogue.saving_state==1)
                    {
                        save_level(game);
                        continuer=0;
                    }
                    else
                        continuer=0;
                }

                if (game->global.EOL)
                    load_next_level(game);

                if (game->global.on_door)
                    teleport_next_door(game);

                if(pick_item(game)==0)
                    drop_item(game);



                break;

            case SDLK_f:
                game->background.scroll_x+=80;
                break;

            default:
                break;

            }

    }


    return continuer;
}
