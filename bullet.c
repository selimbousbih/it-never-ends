/**

* @file bullet.c

* @author C Squad

* @version 1.0

* @date May 14, 2016

*/

#include <math.h>
#include <string.h>
#include "game.h"
#include "functions.h"

#define BULLET_TICKS 4000

int collision_cercle(Cercle c1, Cercle c2);

int get_elapsed=1;

void init_bullet(GAME *game, int a, int b) /* a: npc id     b: bullet id */
{
    if (game->character.position.x+game->background.scroll_x<game->npc[a].position.x)
    {
        game->objects.bullet[b].direction=-1;
        game->objects.bullet[b].position.x=game->npc[a].position.x;
        game->objects.bullet[b].position.y=game->npc[a].position.y+15;
    }
    else
    {
        game->objects.bullet[b].direction=1;
        game->objects.bullet[b].position.x=game->npc[a].position.x+20;
        game->objects.bullet[b].position.y=game->npc[a].position.y+15;

    }
}

void blit_bullet(GAME *game)
{
    int i=0;

    SDL_Rect src_bullet;
    src_bullet.x=0;
    src_bullet.y=0;
    src_bullet.h=12;
    src_bullet.w=20;

    for (i=0; i<5; i++)
    {
        if (SDL_TICKS_PASSED(game->objects.bullet[i].ticks, BULLET_TICKS))
            game->objects.bullet[i].started=0;

        if (game->objects.bullet[i].started)
        {
            game->objects.bullet[i].position.x+=game->objects.bullet[i].direction*game->objects.bullet[i].speed;
            game->objects.bullet[i].cercle.x=game->objects.bullet[i].position.x;
            game->objects.bullet[i].cercle.y=game->objects.bullet[i].position.y;


            SDL_BlitSurface(game->objects.bullet[i].image, &src_bullet, game->screen, &game->objects.bullet[i].relativePos);


            /* collision start */
            if (!game->character.died)
                if (collision_cercle(game->character.pos_cercle,game->objects.bullet[i].cercle))
                {
                    game->character.died=1;
                    game->character.life--;
                    game->objects.bullet[i].started=0;
                }
            /* collision end */
        }
    }

}


void bullet_shot(GAME *game, int a)  /* a: npc id */
{
    int i=0;

    if (get_elapsed)
    {
        game->objects.elapsed=SDL_GetTicks();
        get_elapsed=0;


        while (i<5)
        {
            if (!game->objects.bullet[i].started)
            {
                init_bullet(game,a,i);
                game->objects.bullet[i].ticks=SDL_GetTicks();
                game->objects.bullet[i].started=1;

                if (SDL_TICKS_PASSED(game->objects.bullet[i].ticks, BULLET_TICKS))
                    get_elapsed=0;
                i=5;

            }
            else
                i++;
        }

    }
            if (SDL_TICKS_PASSED(game->objects.elapsed, RELOAD))
            get_elapsed=1;
}


/*
void bullet_shot(GAME *game, int a)   a: npc id   -- old fct
{
    int i=0;

    //if (!game->objects.bullet[0].started)
    if (get_elapsed)
        {
            game->objects.elapsed=SDL_GetTicks();
            get_elapsed=0;
        }

    for (i=0; i<5; i++)
    {
        if (!game->character.died)
            if (collision_cercle(game->character.pos_cercle,game->objects.bullet[i].cercle))
            {
                game->character.died=1;
                game->character.life--;
                game->objects.bullet[i].started=0;
            }

        if (SDL_TICKS_PASSED(game->objects.elapsed,i*RELOAD))
        {
            if (!game->objects.bullet[i].started)
            {
                init_bullet(game,a,i);
                game->objects.bullet[i].started=1;
   //             fprintf(stderr,"he %d\n",game->objects.bullet[i].position.x);
            }
        }
        if (i==4)
            if (SDL_TICKS_PASSED(game->objects.elapsed,(i+1)*RELOAD))
                get_elapsed=1;
    }
}
*/
