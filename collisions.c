/**

* @file collisions.c

* @author C Squad

* @version 1.0

* @date May 14, 2016

*/

#include <math.h>
#include "game.h"

int collision_cercle(Cercle c1, Cercle c2)
{
    return(sqrt(pow((c1.x-c2.x),2)+pow((c1.y-c2.y),2)) <= (c1.r+c2.r));
}


int collision_box(Box b1, Box b2)
{
    return(b1.x > b2.x-8 && b1.x < b2.x+8);
}

//Lire les couleurs d'un pixel
SDL_Color GetPixel(SDL_Surface *Background, int x, int y)
{
    SDL_Color color, black={255,255,255};
    Uint32 col = 0;
    //Determine position

if (x<10000 && y<600)
{
    char *pixelPosition = (char*)Background->pixels;
    //Offset by Y
    pixelPosition += (Background->pitch * y);
    //Offset by X
    pixelPosition += (Background->format->BytesPerPixel * x);
    //Copy pixel data
    memcpy(&col, pixelPosition, Background->format->BytesPerPixel);
    //Convert to color
    SDL_GetRGB(col, Background->format, &color.r, &color.g, &color.b);

    return (color);
}
else
    return (black);

}

int Collision_PPP(GAME *game, Character perso)
{
    SDL_Color PixelToCompare;

SDL_LockSurface(game->background.levelCollision);
    if (game->input.left)
    {
        if (game->character.position.x + game->background.scroll_x + game->character.position.w*3/4 > 0)
        PixelToCompare = GetPixel(game->background.levelCollision, game->character.position.x + game->background.scroll_x+game->character.position.w/4, game->character.position.y+game->character.position.h-(game->config.resolution_h-game->background.levelCollision->h)/2-12);

        return ((PixelToCompare.r == 255) && (PixelToCompare.b == 255) && (PixelToCompare.g == 255));
    }

    if (game->input.right)
    {
        if (game->character.position.x + game->background.scroll_x + game->character.position.w*3/4 < game->background.levelCollision->w)
        PixelToCompare = GetPixel(game->background.levelCollision, game->character.position.x + game->background.scroll_x + game->character.position.w*3/4, game->character.position.y+game->character.position.h-(game->config.resolution_h-game->background.levelCollision->h)/2-12);

        return ((PixelToCompare.r == 255) && (PixelToCompare.b == 255) && (PixelToCompare.g == 255));
    }
SDL_UnlockSurface(game->background.levelCollision);
    return 0;
}

int onGround(GAME *game, Character perso)
{
    SDL_Color PixelToCompare;
    PixelToCompare = GetPixel(game->background.levelCollision /*Background*/, game->character.position.x + game->background.scroll_x + game->character.position.w / 2, game->character.position.y+game->character.position.h-(game->config.resolution_h-game->background.levelCollision->h)/2);
    return ((PixelToCompare.r == 255) && (PixelToCompare.b == 255) && (PixelToCompare.g == 255));
}
/*
int onGround(GAME *game, Character perso)
{
    SDL_Color PixelToCompare;
    PixelToCompare = GetPixel(game->background.levelCollision , game->character.position.x + game->background.scroll_x + game->character.position.w / 2, game->character.position.y+game->character.position.h-(game->config.resolution_h-PLAT_H)/2);
    return ((PixelToCompare.r == 255) && (PixelToCompare.b == 255) && (PixelToCompare.g == 255));
}*/

int onTexte(GAME *game)
{
    SDL_Color PixelToCompare;
    PixelToCompare = GetPixel(game->background.levelCollision, game->character.position.x + game->background.scroll_x + game->character.position.w / 2, game->character.position.y+game->character.position.h/2-(game->config.resolution_h-game->background.levelCollision->h)/2);

    if ((PixelToCompare.b == 0) && (PixelToCompare.g == 0) && (PixelToCompare.r%50==0))
        return (PixelToCompare.r / 50);
    else
        return 0;
}


int collision_pente(GAME *game)
{
/* Given actual position x1 checks if f(x2)=ax2 is a white pixel, if so then we have a slope */
/* for x1=0 and x2=10 f(x2)=4 */

    SDL_Color PixelToCompare;
    PixelToCompare = GetPixel(game->background.levelCollision, game->character.position.x +10+ game->background.scroll_x + game->character.position.w / 2, game->character.position.y+GRAVITY-4+game->character.position.h-(game->config.resolution_h-game->background.levelCollision->h)/2);

    return ((PixelToCompare.r == 255) && (PixelToCompare.b == 255) && (PixelToCompare.g == 255));
}


int collision_fall(GAME *game)
{
    SDL_Color PixelToCompare;
    PixelToCompare = GetPixel(game->background.levelCollision, game->character.position.x + game->background.scroll_x + game->character.position.w / 2, game->character.position.y+game->character.position.h-(game->config.resolution_h-game->background.levelCollision->h)/2);
    return ((PixelToCompare.r == 255) && (PixelToCompare.b == 0) && (PixelToCompare.g == 0));
}

Color collision_color(GAME *game)
{
    SDL_Color PixelToCompare;
    PixelToCompare = GetPixel(game->background.levelCollision, game->character.position.x + game->background.scroll_x + game->character.position.w / 2, game->character.position.y+game->character.position.h/2-(game->config.resolution_h-game->background.levelCollision->h)/2);
    if ((PixelToCompare.r == 255) && (PixelToCompare.b == 0) && (PixelToCompare.g == 0))
        return RED;
    else if ((PixelToCompare.r == 0) && (PixelToCompare.b == 255) && (PixelToCompare.g == 0))
        return BLUE;
    else if ((PixelToCompare.r == 0) && (PixelToCompare.b == 0) && (PixelToCompare.g == 255))
        return GREEN;
    else if ((PixelToCompare.r == 255) && (PixelToCompare.b == 0) && (PixelToCompare.g == 255))
        return YELLOW;
    else
        return NONE;
}
