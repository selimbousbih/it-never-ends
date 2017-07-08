/**

* @file enemy.c

* @author C Squad

* @version 1.0

* @date May 14, 2016

*/


#include <math.h>
#include "game.h"
#include "functions.h"

unsigned int src_pos=1;

int inrange(GAME *game, int i)
{
    return (sqrt(pow(game->npc[i].position.x-(game->background.scroll_x+game->character.position.x),2))<game->npc[i].vision_range && (game->character.position.y >= game->npc[i].position.y - CHAR_H && game->character.position.y <= game->npc[i].position.y + CHAR_H));
}

int spotted(GAME *game, int i)
{
    return ((game->character.position.x+game->background.scroll_x < game->npc[i].position.x && game->npc[i].direction == -1) || (game->character.position.x+game->background.scroll_x > game->npc[i].position.x && game->npc[i].direction == 1) ) ;
}

void movement_npc(GAME *game, int n)
{

        if (game->npc[n].behavior==PATROL || game->npc[n].behavior==REFRACT)
        {
            if (!game->npc[n].fix)
            {
                game->npc[n].elapsed=SDL_GetTicks();
                game->npc[n].fix=1;
            }


            game->npc[n].position.x+=game->npc[n].speed*game->npc[n].direction;

            if (SDL_TICKS_PASSED(game->npc[n].elapsed, 5000))
            {
                game->npc[n].direction*=(-1);
                game->npc[n].fix=0;
            }

            if (game->npc[n].direction==1)
                game->npc[n].look=0;

            else
                game->npc[n].look=1;

            game->npc[n].actuel++;
            if (game->npc[n].actuel>4)
                game->npc[n].actuel=0;
        }

        else if (game->npc[n].behavior==ATTACK)
        {
            if (game->npc[0].direction==1)
            {
                game->npc[0].look=2;
                game->npc[0].actuel=0;
            }
            else
            {
                game->npc[0].look=2;
                game->npc[0].actuel=1;
            }

		bullet_shot(game, n);

        }



        if (inrange(game,n))
        {
            if (spotted(game,n))
                {
                    if (game->global.get_elapsed_npc[n])
                    {
                        game->global.get_elapsed_npc[n]=0;
                        game->global.elapsed_npc[n] = SDL_GetTicks();
                    }
                    else
                    {
                        if (SDL_TICKS_PASSED(game->global.elapsed_npc[n], 600))
                            game->npc[n].behavior=ATTACK;
                        else
                            game->npc[n].behavior=REFRACT;
                    }

                }

        }
        else
        {
            game->npc[n].behavior=PATROL;
            game->global.get_elapsed_npc[n]=1;
        }




}


