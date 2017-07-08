#include "game.h"

/**

* @file menuQuit.c

* @author C Squad

* @version 1.0

* @date May 14, 2016

*/

void saving_menu(GAME *game, Dialogue dialogue)
{
	dialogue.btnYes = dialogue.saveYESa;
	dialogue.btnNo = dialogue.saveNOb;

	if (dialogue.interrupt == 1)
	{
		if (dialogue.saving_state == 1)
		{
			dialogue.btnYes = dialogue.saveYESa;
			dialogue.btnNo = dialogue.saveNOb;

		}
		else if (dialogue.saving_state == 2)
		{
			dialogue.btnYes = dialogue.saveYESb;
			dialogue.btnNo = dialogue.saveNOa;
		}

        SDL_BlitSurface(dialogue.dialogue, NULL, game->screen, &dialogue.positionD);
        SDL_BlitSurface(dialogue.btnYes, NULL, game->screen, &dialogue.positionYES);
        SDL_BlitSurface(dialogue.btnNo, NULL, game->screen, &dialogue.positionNO);


	SDL_Flip(game->screen);

	}

}

void load_menuQuit(GAME *game)
{

	game->dialogue.dialogue = IMG_Load("DATA/GFX/GUI/Savingame.png");
	game->dialogue.saveYESa = IMG_Load("DATA/GFX/GUI/yesa.png");
	game->dialogue.saveYESb = IMG_Load("DATA/GFX/GUI/yesb.png");
	game->dialogue.saveNOa = IMG_Load("DATA/GFX/GUI/noa.png");
	game->dialogue.saveNOb = IMG_Load("DATA/GFX/GUI/nob.png");

    game->dialogue.positionD.x = (game->config.resolution_w-game->dialogue.dialogue->w)/2;
	game->dialogue.positionD.y = 101;
	game->dialogue.positionYES.x = 182 + (game->config.resolution_w-game->dialogue.dialogue->w)/2;
	game->dialogue.positionYES.y = 420;
	game->dialogue.positionNO.x = 382+(game->config.resolution_w-game->dialogue.dialogue->w)/2;
	game->dialogue.positionNO.y = 420;

}

int save_level(GAME *game)
{
	FILE *fichier = NULL;
	fichier = fopen("save.bin", "wb");
	if (fichier == NULL)
		return 0;
	else
    {
        fwrite(&game->level, sizeof(int), 1, fichier);
        fclose(fichier);
    }
	return 1;

}

int load_level(GAME *game)
{
	FILE *fichier = NULL;
	fichier = fopen("save.bin", "rb");
	if (fichier == NULL)
		return 0;
	else
    {
        fread(&game->level, sizeof(int), 1, fichier);
        fclose(fichier);
        //loadLevel(game);
        return 1;
    }

}


