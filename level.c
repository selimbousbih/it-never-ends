#include <windows.h>
#include "game.h"
#include "functions.h"
#include "level.h"

/**

* @file level.c

* @brief contains the game loop

* @author C Squad

* @version 1.2

* @date May 20, 2016

**/

void level1 (GAME *game);
void display (GAME *game);


void loadLevel(GAME *game)
{
    load_music(game);
    init_level(game);

    SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 0, 0, 0));
    play_music(&game->musique);
    game->global.animate=0;
}

void load_next_level(GAME *game)
{
    game->level++;
    game->global.stopDisplay=1;
    Mix_PauseMusic();
    game->global.stopDisplay=0;

    //free_memory(game);
    loadLevel(game);

}


void reload_this_level(GAME *game)
{
    game->global.stopDisplay=1;
    Mix_PauseMusic();
    game->global.stopDisplay=0;

    //free_memory(game);
    loadLevel(game);

}


void playLevel (GAME *game)
{
    int continuer=1;
    SDL_Event event;


    unsigned int elapsed;
    unsigned int lasttime = SDL_GetTicks();

    load_menuQuit(game);
    loadLevel(game);

    game->global.stopDisplay=0;

    while(continuer)
    {
        lasttime = SDL_GetTicks();

        if(!manage_events(game, &event))
            continuer=0;

        if (!game->character.died)
        {
            if (game->level==1)
                level1(game);
            else if (game->level==2)
                level2(game);
            else if (game->level==3)
                level3(game);
            else if (game->level==4)
                level4(game);
        }

        display(game);


        if (game->global.FIN)
        {
            if (continuer)
            {
                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 1024) == -1)
                {
                    printf("[-] %s", Mix_GetError());
                }
                continuer=0;
                Mix_PauseMusic();
                play_video(game,"OUTRO.mpg");
            }
        }


        if (game->dialogue.interrupt)
            saving_menu(game,game->dialogue);


        if (game->level!=4)
        {
            if (collision_cercle(game->character.pos_cercle, game->objects.objective.cercle))  //Level ends here
            {
                game->global.EOL=1;
                strcpy(game->texte.message,"Press Enter to advance");
                game->global.show_message=1;
                game->texte.position.x=game->character.position.x + 50;
                game->texte.position.y=game->character.position.y - 40;
            }
            else
            {
                if (game->global.EOL)
                    game->global.show_message=0;

                game->global.EOL=0;

            }

        }


        elapsed = SDL_GetTicks()-lasttime;
        if (elapsed<1000/FPS)
            SDL_Delay(1000/FPS-elapsed);

    }
    game->global.stopDisplay=1;
    SDL_Delay(100);
    fclose(game->texte.f);
    TTF_CloseFont(game->texte.police);

//    free_memory(game);

}

void playTutorial (GAME *game)
{
    int i=0;

    for (i=1;i<9;i++)
    {
        SDL_BlitSurface(game->objects.tutorial[i],NULL,game->screen,&game->objects.pos_tuto);
        SDL_BlitSurface(game->objects.tutorial[0],NULL,game->screen,&game->objects.pos_tuto);
        SDL_Flip(game->screen);
        SDL_Delay(600);
    }

}
void level1 (GAME *game)
{
    if (!game->gui.show_dialogue && !game->gui.show_inv)
        movement(game);

    movement_npc(game, 0);
    movement_npc(game, 2);
    movement_npc(game, 3);

    if (onTexte(game)>0)    //collision pixel par pixel to check dialogue
    {
        game->character.look=4;
        game->character.actuel=0;
        if(!game->global.fix)
        {
            game->texte.actuel=onTexte(game);
            if (game->texte.actuel==1)
                game->npc[1].actuel=1;
            game->gui.show_dialogue=1;
            game->global.fix=1;
        }
    }
    else
    {
        game->npc[1].actuel=0;
        game->global.fix=0;
        game->texte.fix=0;
        game->gui.show_dialogue=0;
        game->texte.i=0;
    }

   if (TRUE_X>3500)
        game->global.checkpoint=3500;
    else if (TRUE_X>1200)
        game->global.checkpoint=1200;


}


void level2 (GAME *game)
{
    int i=0;

    if (!game->gui.show_dialogue && !game->gui.show_inv)
    {
        movement(game);
        if (TRUE_X>8180)
        {
            if (game->objects.inventory.item[2].have==0 || game->objects.inventory.item[3].have==0)
                game->background.scroll_x-=SPEED;
        }
    }


    for (i=0; i<5; i++)
    {
        if (collision_cercle(game->character.pos_cercle,game->objects.door[i]))
        {
            sprintf(game->texte.message,"Press Enter");
            game->global.on_door=1;
            game->global.show_message=1;
            game->texte.position.x=game->character.position.x + 30;
            game->texte.position.y=game->character.position.y - 40;
            break;
        }
        else
        {
            if (game->global.on_door)
            {
                game->global.on_door=0;
                game->global.show_message=0;
            }
        }
    }


    if (onTexte(game)>0)    //collision pixel par pixel to check dialogue
    {
        if (game->input.enter)
        {

            if(!game->global.fix)
            {
                game->texte.actuel=onTexte(game);
                game->gui.show_dialogue=1;
                game->global.fix=1;
            }
        }
        else
        {
            sprintf(game->texte.message,"Press Enter");
            game->global.on_door=1;
            game->global.show_message=1;
            game->texte.position.x=game->character.position.x + 30;
            game->texte.position.y=game->character.position.y - 40;
        }
    }
    else
    {
        game->global.fix=0;

        game->gui.show_dialogue=0;
        game->texte.fix=0;
        game->texte.i=0;
        game->input.enter=0;
    }




    if (game->global.level2_show_items)
    {
        for (i=2; i<4; i++)
            if (collision_cercle(game->character.pos_cercle, game->objects.inventory.item[i].cercle))
                if (game->objects.inventory.item[i].have==0)
                {
                    sprintf(game->texte.message,"Press Enter");
                    game->global.on_door=1;
                    game->global.show_message=1;
                    game->texte.position.x=game->character.position.x + 30;
                    game->texte.position.y=game->character.position.y - 40;
                }

        if (collision_color(game)==GREEN)
        {

            sprintf(game->texte.message,"Press Enter");
            game->global.green_item=1;
            game->global.show_message=1;
            game->texte.position.x=game->character.position.x + 30;
            game->texte.position.y=game->character.position.y - 40;

        }
            else if (game->global.green_item)
            {
                game->global.blue_item=0;
                game->global.show_message=0;
                game->global.green_item=0;
            }


    }
    else if (game->background.scroll_x>7000)
        game->global.level2_show_items=1;


}

void level3 (GAME *game)
{
    int i=0;
    if (!game->gui.show_inv)
        movement_level3(game);



    for (i=0; i<11; i++)
    {
        if (collision_cercle(game->character.pos_cercle,game->objects.door[i]))
        {
            sprintf(game->texte.message,"Press Enter");
            game->global.on_door=1;
            game->global.show_message=1;
            game->texte.position.x=game->character.position.x + 30;
            game->texte.position.y=game->character.position.y - 40;
            break;
        }
        else
        {
            if (game->global.on_door)
            {
                game->global.on_door=0;

                game->global.show_message=0;
            }
        }

    }


    if (collision_cercle(game->character.pos_cercle, game->objects.inventory.item[1].cercle))
        if (game->objects.inventory.item[1].have==0)
        {
            sprintf(game->texte.message,"Press Enter");
            game->global.on_door=1;
            game->global.show_message=1;
            game->texte.position.x=game->character.position.x + 30;
            game->texte.position.y=game->character.position.y - 40;
        }


    SDL_Delay(2);
}

void level4 (GAME *game)
{
    if (game->character.position.x < 150 || collision_fall(game))
    {
        SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 0, 0, 0));

        loading_screen(game);
        game->character.life--;
        game->background.scroll_x=0;
        game->character.position.x=game->config.resolution_w/2;
    }

    if (collision_cercle(game->character.pos_cercle, game->objects.objective.cercle))
    {
        SDL_Delay(300);
        game->global.FIN=1;
    }

    if (!game->global.FIN)
    {

        if (game->background.scroll_x<8600)
        {
            game->input.right=1;
            mouvement_level4(game);
            game->input.right=0;
        }
        else
        {
            //movement(game);
            game->input.right=1;
            mouvement_level4(game);
            game->input.right=0;
            SDL_Delay(15);
        }


    }

}


void teleport_next_door(GAME *game)
{
    int i=0;
    if (game->level==2)
    {
        for (i=0; i<5; i++)
        {
            if (collision_cercle(game->character.pos_cercle,game->objects.door[i]))
            {
                if (TRUE_X<=game->objects.door[i].x)
                {
                    game->character.position.x=50;
                    if (game->background.scroll_x+2*game->config.resolution_w<game->background.image[0]->w)
                        game->background.scroll_x+=game->config.resolution_w;
                    else
                    {
                        game->background.scroll_x=game->background.image[0]->w-game->config.resolution_w;
                        game->character.position.x+=200;
                    }
                }
                else
                {
                    game->character.position.x=game->config.resolution_w-100;
                    game->background.scroll_x-=game->config.resolution_w;

                }
            }
        }
    }
    else if (game->level==3)
    {
        for (i=0; i<11; i++)
        {
            if (collision_cercle(game->character.pos_cercle,game->objects.door[i]))
            {
                switch(i)
                {
                case 0:
                    game->background.scroll_x=6240-22;
                    game->character.position.x=game->objects.door[1].x-game->background.scroll_x;
                    break;
                case 1:
                    game->background.scroll_x=3265-22;
                    game->character.position.x=game->objects.door[7].x-game->background.scroll_x;
                    break;
                case 2:
                    game->background.scroll_x=4765-22;
                    game->character.position.x=game->objects.door[3].x-game->background.scroll_x;
                    break;
                case 3:
                    game->background.scroll_x=4765-22;
                    game->character.position.x=game->objects.door[5].x-game->background.scroll_x;
                    break;
                case 4:
                    game->background.scroll_x=3265-22;
                    game->character.position.x=game->objects.door[6].x-game->background.scroll_x;
                    break;
                case 5:
                    game->background.scroll_x=1780-22;
                    game->character.position.x=game->objects.door[9].x-game->background.scroll_x;
                    break;
                case 6:
                    game->background.scroll_x=6240-22;
                    game->character.position.x=game->objects.door[1].x-game->background.scroll_x;
                    break;
                case 7:
                    game->background.scroll_x=6240-22;
                    game->character.position.x=game->objects.door[2].x-game->background.scroll_x;
                    break;
                case 8:////
                    game->background.scroll_x=242-22;
                    game->character.position.x=game->config.resolution_w/2;
                    break;
                case 9:
                    game->background.scroll_x=6240-22;
                    game->character.position.x=game->objects.door[1].x-game->background.scroll_x;
                    break;
                }
            }
        }
    }
}


void display(GAME *game)
{
    if (!game->global.stopDisplay)
    {
        game->background.counter++;
        if (game->background.counter>100)
            game->background.counter=0;//rand()%100;

        getPositions(game);
        update_screen(game);

    }
}
