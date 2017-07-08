#include "game.h"
#include <smpeg/smpeg.h>

/**

* @file intro.c

* @author C Squad

* @version 1.0

* @date May 14, 2016

*/

void play_video(GAME *game, char filename[30]);

void get_out()
{
    //TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}
void intro(GAME *game)
{
    play_video(game,"cinematique.mpg");
}

void play_video(GAME *game, char filename[30])
{
    SDL_Surface *surfaceVideo = NULL;
    SDL_Rect position;

    int continuer = 1;
    SDL_Event event;
    char file[50]=" ";
    sprintf(file,"DATA/cinematiques/%s",filename);
    SMPEG_Info mpg_info;
    SMPEG *mpg = NULL;

    mpg = SMPEG_new(file, &mpg_info, 1);

    surfaceVideo = SDL_AllocSurface(SDL_HWSURFACE, mpg_info.width, mpg_info.height, game->screen->format->BitsPerPixel, game->screen->format->Rmask, game->screen->format->Gmask, game->screen->format->Bmask, game->screen->format->Amask);
    if (surfaceVideo == NULL)
    {
        fprintf(stderr, "Impossible d'allouer la surface vidéo");
        exit(EXIT_FAILURE);
    }

    SMPEG_setdisplay(mpg, surfaceVideo, NULL, NULL);
    SMPEG_play(mpg);

    position.x=(game->config.resolution_w-surfaceVideo->w)/2;
    position.y=(game->config.resolution_h-surfaceVideo->h)/2;;

    while (continuer)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym==SDLK_SPACE)
                    continuer=0;
                if (event.key.keysym.sym==SDLK_ESCAPE)
                    get_out();
                break;
            }
        }

        if (SMPEG_status(mpg) != SMPEG_PLAYING)
            continuer = 0;

        SDL_BlitSurface(surfaceVideo, NULL, game->screen, &position);
        SDL_Flip(game->screen);
    }

    SMPEG_stop(mpg);
    SMPEG_delete(mpg);
    mpg = NULL;

    SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 0, 0, 0));
    SDL_FreeSurface(surfaceVideo);
    surfaceVideo = NULL;

}
