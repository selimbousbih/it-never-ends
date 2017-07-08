/**

* @file display.c

* @author C Squad

* @version 1.0

* @date May 14, 2016

*/


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "game.h"
#include "functions.h"
#include "display.h"

int fix_wasted=0;
void BlitWasted(GAME *game, SDL_Rect pos_screen);

void update_screen(GAME *game)
{
    unsigned int elapsed;
    unsigned int lasttime = SDL_GetTicks();
    int i=0;
    SDL_Rect pos_screen;

    pos_screen.x=0;
    pos_screen.y=(game->config.resolution_h-game->background.image[0]->h)/2;

    game->background.position.x=game->background.scroll_x;
    game->background.position.y=game->background.scroll_y;
    game->background.position.h=PLAT_H;
    game->background.position.w=PLAT_W;

    game->objects.objective.pos_src.w=62;
    game->objects.objective.pos_src.h=90;
    game->objects.objective.pos_src.x=game->global.obj_i*62;
    game->objects.objective.pos_src.y=0;

    if (game->level==1)
    {
        game->character.src_pos.x=CHAR_W*game->character.actuel;
        game->character.src_pos.y=CHAR_H*game->character.look;
        game->character.src_pos.h=CHAR_H;
        game->character.src_pos.w=CHAR_W;
    }
    else
    {
        game->character.src_pos.x=CHAR_BIG_W*game->character.actuel;
        game->character.src_pos.y=CHAR_BIG_H*game->character.look;
        game->character.src_pos.h=CHAR_BIG_H;
        game->character.src_pos.w=CHAR_BIG_W;
    }

    i=(game->background.counter%3)+2;

    if (/*!game->character.died && */game->background.image[0]!=NULL)
    {
        SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 0, 0, 0));
        switch (game->level)
        {
        case 1:
            if (random_case(game))
                SDL_BlitSurface(game->background.image[1],&game->background.position,game->screen,&pos_screen);
            else
                SDL_BlitSurface(game->background.image[0],&game->background.position,game->screen,&pos_screen);

            break;
        case 2:
            if (game->background.counter%10)
                SDL_BlitSurface(game->background.image[1],&game->background.position,game->screen,&pos_screen);
            else
                SDL_BlitSurface(game->background.image[0],&game->background.position,game->screen,&pos_screen);
            if (game->global.level2_show_items)
                SDL_BlitSurface(game->background.image[2],&game->background.position,game->screen,&pos_screen);

            if (game->global.level2_show_items)
            {
                if (game->objects.inventory.item[2].have==0)
                    SDL_BlitSurface(game->objects.inventory.item[2].image,NULL,game->screen,&game->objects.inventory.item[2].blit_pos);
                if (game->objects.inventory.item[3].have==0)
                    SDL_BlitSurface(game->objects.inventory.item[3].image,NULL,game->screen,&game->objects.inventory.item[3].blit_pos);
            }
            break;
        case 3:
            SDL_BlitSurface(game->background.image[i%2],&game->background.position,game->screen,&pos_screen);
            if (game->objects.inventory.item[1].have==0)
                SDL_BlitSurface(game->objects.inventory.item[1].image,NULL,game->screen,&game->objects.inventory.item[1].blit_pos);

            break;
        case 4:
//       SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 0, 0, 0));
            SDL_BlitSurface(game->background.image[0],&game->background.position,game->screen,&pos_screen);
            break;

        }


        game->global.obj_i++;
        if (game->global.obj_i>7)
            game->global.obj_i=0;

        game->objects.objective.pos_src.x=game->global.obj_i*62;
        game->objects.objective.pos_src.y=0;

        if (game->objects.objective.image!=NULL)
            if (PLAT_W+game->background.scroll_x>=game->objects.objective.position.x)
            {
                SDL_BlitSurface(game->objects.objective.image,&game->objects.objective.pos_src,game->screen,&game->objects.objective.relativePos);
            }


        /* --- */
        BlitNPC(game);
        SDL_BlitSurface(game->character.image,&game->character.src_pos,game->screen,&game->character.position);

        if (game->level==1)
            SDL_BlitSurface(game->background.image[i],&game->background.pos_rain,game->screen,&pos_screen);
        if (game->level==4)
        {
            game->global.fire_i++;
            if (game->global.fire_i>3)
                game->global.fire_i=0;

            if (!game->global.FIN)
                SDL_BlitSurface(game->background.image[game->global.fire_i+2],NULL,game->screen,&pos_screen);

        }

        SDL_BlitSurface(game->gui.avatar,NULL,game->screen,&game->gui.pos_avatar);
        game->gui.hp = TTF_RenderText_Solid(game->texte.police, tostr(game->character.life), game->texte.couleur);
        SDL_BlitSurface(game->gui.hp, NULL, game->screen, &game->gui.pos_hp);

        /* inventaire */
        if (game->gui.show_inv)
        {
            show_inventory(game);
        }


        /* Dialogue */
        if (game->gui.show_dialogue)
        {
            SDL_BlitSurface(game->gui.dialogue[game->texte.indice[game->texte.i]], NULL, game->screen, &game->gui.pos_dialogue);
            SDL_BlitSurface(game->gui.btn_animated[i%2], NULL, game->screen, &game->gui.pos_btn);
            blit_text(game);
        }

        /* Shooting */
        blit_bullet(game);

        /* Text */
        if (game->global.show_message)
            show_message(game);


        /* */

        if (game->character.life<=0)// && game->texte.quote!=NULL)
            SDL_BlitSurface(game->texte.quote, NULL, game->screen, NULL);

        if (game->character.died)
        {
            if (!game->global.fix_died)
            {
                game->global.frame_died++;
                if (game->global.frame_died==32)
                    game->global.fix_died=1;
                SDL_Delay(game->global.frame_died);
                pos_screen.x+=100;
                SDL_BlitSurface(game->gui.died[game->global.frame_died], NULL, game->screen, &pos_screen);
                pos_screen.x-=100;
            }
            else
            {
                pos_screen.x+=100;
                SDL_BlitSurface(game->gui.died[32], NULL, game->screen, &pos_screen);
                game->global.frame_died=0;
                pos_screen.x-=100;
            }
        }
        //fix_wasted=0;
    }

    /*else
    {

    }*/


    /* Fixing fps */
    elapsed = SDL_GetTicks()-lasttime;
    if (elapsed<1000/FPS)
        SDL_Delay(1000/FPS-elapsed);

    SDL_Flip(game->screen);
}

void BlitNPC(GAME *game)
{
    SDL_Rect src_npc[5]; //relativePos_npc takes the position relative to camera from actual position


    src_npc[0].x=CHAR_W*game->npc[0].actuel;
    src_npc[0].y=CHAR_H*game->npc[0].look;
    src_npc[0].h=CHAR_H;
    src_npc[0].w=CHAR_W;

    src_npc[1].x=CHAR_W*game->npc[1].actuel;
    src_npc[1].y=CHAR_H*game->npc[1].look;
    src_npc[1].h=CHAR_H;
    src_npc[1].w=CHAR_W;

    src_npc[2].x=CHAR_W*game->npc[2].actuel;
    src_npc[2].y=CHAR_H*game->npc[2].look;
    src_npc[2].h=CHAR_H;
    src_npc[2].w=CHAR_W;

    src_npc[3].x=CHAR_W*game->npc[3].actuel;
    src_npc[3].y=CHAR_H*game->npc[3].look;
    src_npc[3].h=CHAR_H;
    src_npc[3].w=CHAR_W;

    if (game->npc[4].image!=NULL)
    {
        src_npc[4].x=0;//85*game->npc[4].actuel;
        src_npc[4].y=150;//150*game->npc[4].look;
        src_npc[4].h=150;
        src_npc[4].w=78;
    }


    if (game->npc[0].image!=NULL)
        if (PLAT_W+game->background.scroll_x>=game->npc[0].position.x)
        {
            SDL_BlitSurface(game->npc[0].image,&src_npc[0],game->screen,&game->npc[0].relativePos);
        }
    if (game->npc[1].image!=NULL)
        if (PLAT_W+game->background.scroll_x>=game->npc[1].position.x)
        {
            SDL_BlitSurface(game->npc[1].image,&src_npc[1],game->screen,&game->npc[1].relativePos);
        }

    if (game->npc[2].image!=NULL)
        if (PLAT_W+game->background.scroll_x>=game->npc[2].position.x)
        {
            SDL_BlitSurface(game->npc[2].image,&src_npc[2],game->screen,&game->npc[2].relativePos);
        }
    if (game->npc[3].image!=NULL)
        if (PLAT_W+game->background.scroll_x>=game->npc[3].position.x)
        {
            SDL_BlitSurface(game->npc[3].image,&src_npc[3],game->screen,&game->npc[3].relativePos);
        }

    if (game->npc[4].image!=NULL)
    {
        if (PLAT_W+game->background.scroll_x>=game->npc[4].position.x)
        {
            SDL_BlitSurface(game->npc[4].image, &src_npc[4],game->screen, &game->npc[4].relativePos);
        }

    }

}

void getPositions(GAME *game)
{
    int i=0;
    for (i=0; i<5; i++)
        if (game->npc[i].image!=NULL)
        {
            game->npc[i].relativePos.x=relative_x(game,game->npc[i].position);
            game->npc[i].relativePos.y=game->npc[i].position.y;
        }

    for (i=0; i<5; i++)
        //if (game->objects.bullet[i].started)
    {
        game->objects.bullet[i].relativePos.x=relative_x(game, game->objects.bullet[i].position);
        game->objects.bullet[i].relativePos.y=game->objects.bullet[i].position.y;
    }
    game->objects.objective.relativePos.x=relative_x(game, game->objects.objective.position);
    game->objects.objective.relativePos.y=game->objects.objective.position.y;

    game->objects.inventory.item[1].blit_pos.x=game->objects.inventory.item[1].cercle.x;
    game->objects.inventory.item[1].blit_pos.y=game->objects.inventory.item[1].cercle.y;
    game->objects.inventory.item[1].blit_pos.x=relative_x(game, game->objects.inventory.item[1].blit_pos);
    game->objects.inventory.item[2].blit_pos.x=game->objects.inventory.item[2].cercle.x;
    game->objects.inventory.item[2].blit_pos.y=game->objects.inventory.item[2].cercle.y;
    game->objects.inventory.item[2].blit_pos.x=relative_x(game, game->objects.inventory.item[2].blit_pos);
    game->objects.inventory.item[3].blit_pos.x=game->objects.inventory.item[3].cercle.x;
    game->objects.inventory.item[3].blit_pos.y=game->objects.inventory.item[3].cercle.y;
    game->objects.inventory.item[3].blit_pos.x=relative_x(game, game->objects.inventory.item[3].blit_pos);
}

void show_message(GAME *game)
{
    game->texte.texte = TTF_RenderText_Solid(game->texte.police, game->texte.message, game->texte.couleur);
    SDL_BlitSurface(game->texte.texte, NULL, game->screen, &game->texte.position);
}


void BlitWasted(GAME *game, SDL_Rect pos_screen)
{
    int i=0;
    for (i=1; i<32; i++)
    {
        SDL_BlitSurface(game->gui.died[i], NULL, game->screen, &pos_screen);
        SDL_Flip(game->screen);
        SDL_Delay(40);
    }
}
