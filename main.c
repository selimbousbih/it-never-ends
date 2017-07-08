#include "game.h"

/**

* @file main.c

* @brief It never ends main.

* @author C Squad

* @version 1.0

* @date May 14, 2016

*/

int game_menu(GAME *game);
int get_config(GAME *game);


int main(int argc, char *argv[])
{
    GAME game;
    game.config.fullscreen=0;
    game.config.resolution_h=720;
    game.config.resolution_w=1167;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("It never ends", NULL);
    SDL_WM_SetIcon(IMG_Load("Loupe.png"), NULL);

    if (get_config(&game)==0)
    {
        if (game.config.fullscreen==1)
            game.screen = SDL_SetVideoMode(game.config.resolution_w, game.config.resolution_h, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);
        else
            game.screen = SDL_SetVideoMode(game.config.resolution_w, game.config.resolution_h, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
    }
    else //if file missing set default configuration
        game.screen = SDL_SetVideoMode(1167, 720, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);

//

    TTF_Init();
    /* Main Start */

    intro(&game);

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) //SDL_Mixer Init
    {
        printf("[-] %s", Mix_GetError());
    }

    loading_screen(&game);

   // do
   // {
        start_menu(&game);
 //   }while(game.global.FIN);


    /* Main End */

    SDL_FreeSurface(game.screen);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
    return EXIT_SUCCESS;
}

int get_config(GAME *game)
{
    game->config.f=fopen("config/config.cfg","r");
    if (game->config.f!=NULL)
    {
        fscanf(game->config.f,"[resolution]\n");
        fscanf(game->config.f,"w=%d\n",&game->config.resolution_w);
        fscanf(game->config.f,"h=%d\n",&game->config.resolution_h);
        fscanf(game->config.f,"fullscreen=%d\n",&game->config.fullscreen);
        return 0;
    }
    else
        return -1;

}

void start_menu(GAME *game)
{
    if (game_menu(game)==0)
    {
        playLevel(game);
    }
}
