#include "menu.h"
#include "game.h"

/**

* @file menu.c

* @brief It never ends menu.

* @author C Squad

* @version 1.2

* @date May 23, 2016

*/

void get_out();
int get_config(GAME *game);

int game_menu(GAME *game)
{
    Menu menu;

    int fix=0;
    Mix_Chunk *son;
    son = Mix_LoadWAV("DATA/SFX/wood.ogg");

    SDL_Surface *animation[11]= {NULL};
    SDL_Surface *titre[56];
    SDL_Surface *boutonsA[5]= {NULL};
    SDL_Surface *boutonsB[5]= {NULL};

    SDL_Surface *exit_menu[5]= {NULL};
    SDL_Surface *options_back=NULL;
    SDL_Surface *options[8]= {NULL};

    SDL_Rect positionfond = {0,0,0,0};
    SDL_Rect positionsrc = {0,20,1167,700};
    SDL_Rect positionbouton[5] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

    SDL_Rect positionexit, positionyes, positionno;
    SDL_Rect positionoptions, positionoption1, positionoption2;

    SDL_Event event;
    int TITLE_SHOWN=0;

    int i=0, v=0, j=0;
    char file_name[25]=" ";

    int fix_son=0;

    Mix_Music *musique;

    /* START Music Stuff */

    Mix_AllocateChannels(2);
    musique = Mix_LoadMUS("DATA/SFX/menu.ogg"); //Chargement de la musique

    Mix_VolumeChunk(son, MIX_MAX_VOLUME/8);
    Mix_VolumeMusic(MIX_MAX_VOLUME/4);
    Mix_PlayMusic(musique, -1);

    /* END Music Stuff */


    //Variable initialization

    menu.done=0;
    menu.etat=1;
    menu.SHOW_OPTION=0;
    menu.SHOW_EXIT=0;
    menu.opt1_select=0;
    menu.opt2_select=0;
    menu.exit_yes=0;
    menu.exit_no=0;

    menu.continue_level=0;


    positionfond.x = 0+100;
    positionfond.y = 0;
    positionbouton[0].x = 495+100;
    positionbouton[0].y = 376;
    positionbouton[1].x = 503+100;
    positionbouton[1].y = 446;
    positionbouton[2].x = 513+100;
    positionbouton[2].y = 511;
    positionbouton[3].x = 546+100;
    positionbouton[3].y = 576;
    positionbouton[4].x = 550+100;
    positionbouton[4].y = 639;

    positionoptions.x = 198+100;
    positionoptions.y = 101;
    positionoption1.x = 290+100;
    positionoption1.y = 226;
    positionoption2.x = 370+100;
    positionoption2.y = 317;


    positionexit.x = 198+100;
    positionexit.y = 200;
    positionyes.x = 432+100;
    positionyes.y = 420;
    positionno.x = 634+100;
    positionno.y = 420;


    for (i = 1; i < 10; i++)
    {
        sprintf(file_name, "DATA/GFX/menu/animation/a%d.png", i);
        animation[i] = IMG_Load(file_name);
    }


//Arriere-plan du menu
    for (i = 1; i < 5; i++)
    {
        sprintf(file_name, "DATA/GFX/menu/animation/a%d.png", i);
        animation[i] = IMG_Load(file_name);
    }

//titre
    for (i = 1; i < 55; i++)
    {
        sprintf(file_name, "DATA/GFX/menu/titre/b00%d.png", i);
        titre[i] = IMG_Load(file_name);
    }

//boutons
    for (i=1; i<6; i++)
    {
        sprintf(file_name, "DATA/GFX/menu/boutons/%da.png", i);
        boutonsA[i] = IMG_Load(file_name);

        sprintf(file_name, "DATA/GFX/menu/boutons/%db.png", i);
        boutonsB[i] = IMG_Load(file_name);
    }

//menu exit

    exit_menu[0]=IMG_Load("DATA/GFX/menu/options/Exit.png");
    exit_menu[1]=IMG_Load("DATA/GFX/menu/options/yesb.png");
    exit_menu[2]=IMG_Load("DATA/GFX/menu/options/yesa.png");
    exit_menu[3]=IMG_Load("DATA/GFX/menu/options/nob.png");
    exit_menu[4]=IMG_Load("DATA/GFX/menu/options/noa.png");


//menu_options
    options_back = IMG_Load("DATA/GFX/menu/options/Options.png");
    options[0] = IMG_Load("DATA/GFX/menu/options/OFFb.png");
    options[1] = IMG_Load("DATA/GFX/menu/options/ONb.png");
    options[2] = IMG_Load("DATA/GFX/menu/options/OFFa.png");
    options[3] = IMG_Load("DATA/GFX/menu/options/ONa.png");
    options[4] = IMG_Load("DATA/GFX/menu/options/MUSICONa.png");
    options[5] = IMG_Load("DATA/GFX/menu/options/MUSICOFFa.png");
    options[6] = IMG_Load("DATA/GFX/menu/options/MUSICONb.png");
    options[7] = IMG_Load("DATA/GFX/menu/options/MUSICOFFb.png");


    menu.etat=1;

    i=0;
    v=0;

    menu.continuer=1;
    menu.fullscreenfix=1;

    while (menu.continuer)
    {

        if (menu.opt1_select==1 && !menu.fullscreenfix)
        {
            if (get_config(game)==0)
            {
                game->screen = SDL_SetVideoMode(game->config.resolution_w, game->config.resolution_h, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_FULLSCREEN);
                menu.fullscreenfix=1;
            }
        }

        else if (menu.opt1_select==0 && !menu.fullscreenfix)
        {
            if (get_config(game)==0)
            {
                game->screen = SDL_SetVideoMode(game->config.resolution_w, game->config.resolution_h, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
                menu.fullscreenfix=1;
            }

        }


//************************* Affichage du titre **********************

        if (!TITLE_SHOWN)
        {
            for(v=1; v<53; v++)
            {
                if (i>6)
                    i=0;

                i++;

                SDL_BlitSurface(animation[i],NULL,game->screen,&positionfond);
                SDL_BlitSurface(titre[v],NULL,game->screen,&positionfond);
              //  SDL_Delay(5);
                SDL_Flip(game->screen);
                SDL_FreeSurface(titre[v]);


            }
            TITLE_SHOWN=1;
        }

//********************************************************************

//************************ Animation Background *********************

        if (i>6)
            i=0;

        i++;

        SDL_BlitSurface(animation[i],&positionsrc,game->screen,&positionfond);
        if(!menu.SHOW_EXIT)
        {
            SDL_BlitSurface(titre[54],NULL,game->screen,&positionfond);
            for (j=1; j<6; j++)
                SDL_BlitSurface(boutonsA[j],NULL,game->screen,&positionbouton[j-1]);

            switch(menu.etat)
            {
            case 1:
                SDL_BlitSurface(boutonsB[1],NULL,game->screen,&positionbouton[0]);
                break;
            case 2:
                SDL_BlitSurface(boutonsB[2],NULL,game->screen,&positionbouton[1]);
                break;
            case 3:
                SDL_BlitSurface(boutonsB[3],NULL,game->screen,&positionbouton[2]);
                break;
            case 4:
                SDL_BlitSurface(boutonsB[4],NULL,game->screen,&positionbouton[3]);
                break;
            case 5:
                SDL_BlitSurface(boutonsB[5],NULL,game->screen,&positionbouton[4]);
                break;

            }
        }


//*******************************************************************

//***************************** menu exit ***************************
        if (menu.SHOW_EXIT)
        {
            SDL_BlitSurface(exit_menu[0],NULL,game->screen,&positionexit);
            SDL_BlitSurface(exit_menu[1+menu.exit_yes],NULL,game->screen,&positionyes);
            SDL_BlitSurface(exit_menu[3+menu.exit_no],NULL,game->screen,&positionno);

        }

//*******************************************************************

//**************************** menu options *************************
        if (menu.SHOW_OPTION)
        {
            SDL_BlitSurface(options_back,NULL,game->screen,&positionoptions);
            SDL_BlitSurface(options[menu.opt1_select],NULL,game->screen,&positionoption1);
            SDL_BlitSurface(options[menu.opt2_select],NULL,game->screen,&positionoption2);

        }

//*******************************************************************


        SDL_Flip(game->screen);

        if (SDL_PollEvent(&event)==1)
        {
            if (event.type == SDL_QUIT)
            {
                menu.continuer=0;
            }

            else if (event.type == SDL_KEYUP)
            {
                fix=0;
            }


            else  if (event.type == SDL_KEYDOWN)
            {
                if(!fix)
                {
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_DOWN:
                        if (menu.etat!=5 && !menu.SHOW_OPTION && !menu.SHOW_EXIT)
                        {
                            (menu.etat)++;
                            fix=1;
                            Mix_PlayChannel(1, son, 0);
                        }
                        if (menu.SHOW_OPTION)
                        {
                            if (menu.opt2_select==4)
                                menu.opt2_select=6;
                            if (menu.opt2_select==5)
                                menu.opt2_select=7;
                            if (menu.opt1_select==0)
                                menu.opt1_select=2;
                            if (menu.opt1_select==1)
                                menu.opt1_select=3;
                            fix=1;
                        }
                        break;
                    case SDLK_UP:
                        if (menu.etat!=1 && !menu.SHOW_OPTION && !menu.SHOW_EXIT)
                        {
                            (menu.etat)--;
                            fix=1;
                            Mix_PlayChannel(1, son, 0);
                        }

                        if (menu.SHOW_OPTION)
                        {
                            if (menu.opt1_select==2)
                                menu.opt1_select=0;
                            if (menu.opt1_select==3)
                                menu.opt1_select=1;
                            if (menu.opt2_select==6)
                                menu.opt2_select=4;
                            if (menu.opt2_select==7)
                                menu.opt2_select=5;
                            fix=1;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (menu.SHOW_EXIT)
                        {
                            menu.exit_no=1;
                            menu.exit_yes=0;
                            fix=1;
                        }

                        if (menu.SHOW_OPTION)
                        {
                            if (menu.opt1_select==0)
                            {
                                menu.opt1_select=1;
                                menu.fullscreenfix=0;
                            }

                            if (menu.opt2_select==6)
                            {
                                menu.opt2_select=7;
                                Mix_Pause(1);
                                Mix_PauseMusic();
                            }
                            fix=1;
                        }
                        break;
                    case SDLK_LEFT:
                        if (menu.SHOW_EXIT)
                        {
                            menu.exit_no=0;
                            menu.exit_yes=1;
                            fix=1;
                        }
                        if (menu.SHOW_OPTION)
                        {
                            if (menu.opt1_select==1)
                            {
                                menu.opt1_select=0;
                                menu.fullscreenfix=0;
                            }

                            if (menu.opt2_select==7)
                            {
                                menu.opt2_select=6;
                                Mix_ResumeMusic();
                            }
                            fix=1;
                        }
                        break;

                    case SDLK_ESCAPE:
                        menu.SHOW_OPTION=0;
                        menu.SHOW_EXIT=0;
                        fix=1;
                        break;

                    case SDLK_RETURN:
                        fix=1;
                        switch(menu.etat)
                        {
                        case 1:
                            game->level=1;
                            Mix_PauseMusic();
                            menu.continuer=0;
                            break;

                        case 2:
                            load_level(game);
                            Mix_PauseMusic();
                            menu.continuer=0;
                            break;

                        case 3:
                            if (!menu.SHOW_OPTION)
                            {
                                menu.opt1_select=0;
                                menu.opt2_select=4;
                            }

                            menu.SHOW_OPTION=1;
                            fix=1;
                            break;

                        case 4:
                            break; //help

                        case 5:
                            if(!menu.SHOW_EXIT)
                            {
                                menu.exit_yes=1;
                                menu.exit_no=0;
                            }
                            if (menu.SHOW_EXIT)
                            {
                                if (menu.exit_yes)
                                {
                                    menu.continuer=0;
                                }
                                else
                                    menu.SHOW_EXIT=0;
                            }
                            if(menu.exit_no==0)
                                menu.SHOW_EXIT=1;
                            break;

                        default:
                            break;
                        }
                    default:
                        break;
                    }


                }
            }

            else if (event.type == SDL_KEYUP)
            {
                fix=0;
            }

            else if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.y > 370 && event.motion.y < 690)
            {
                fix=1;
                switch(menu.etat)
                {
                case 1:
                    game->level=1;
                    Mix_PauseMusic();
                    menu.continuer=0;
                    break;

                case 2:
                    load_level(game);
                    Mix_PauseMusic();
                    menu.continuer=0;
                    break;

                case 3:
                    if (!menu.SHOW_OPTION)
                    {
                        menu.opt1_select=0;
                        menu.opt2_select=4;
                    }

                    menu.SHOW_OPTION=1;
                    fix=1;
                    break;

                case 4:
                    break; //help

                case 5:
                    if(!menu.SHOW_EXIT)
                    {
                        menu.exit_yes=1;
                        menu.exit_no=0;
                    }
                    if (menu.SHOW_EXIT)
                    {
                        if (menu.exit_yes)
                        {
                            menu.continuer=0;
                        }
                        else
                            menu.SHOW_EXIT=0;
                    }
                    if(menu.exit_no==0)
                        menu.SHOW_EXIT=1;


                    break;

                default:
                    break;
                }


            }

            if (event.type == SDL_MOUSEMOTION && !menu.SHOW_OPTION && !menu.SHOW_EXIT)
            {
                if ((event.motion.y >= 376) && (event.motion.y <= 428))
                {
                    if(!fix_son)
                        Mix_PlayChannel(1, son, 0);
                    menu.etat = 1;
                    fix_son=1;
                }

                else if ((event.motion.y >= 439) && (event.motion.y <= 492))
                {
                    if(!fix_son)
                        Mix_PlayChannel(1, son, 0);
                    menu.etat = 2;
                    fix_son=1;
                }

                else if ((event.motion.y >= 511) && (event.motion.y <= 566))
                {
                    if(!fix_son)
                        Mix_PlayChannel(1, son, 0);
                    menu.etat = 3;
                    fix_son=1;
                }

                else if ((event.motion.y >= 576) && (event.motion.y <= 630))
                {
                    if(!fix_son)
                        Mix_PlayChannel(1, son, 0);
                    menu.etat = 4;
                    fix_son=1;
                }

                else if ((event.motion.y >= 640) && (event.motion.y <= 685))
                {
                    if(!fix_son)
                        Mix_PlayChannel(1, son, 0);
                    menu.etat = 5;
                    fix_son=1;
                }

                else
                    fix_son=0;

            }

            /* else if (event.type==SDL_QUIT)
             {
                 menu.continuer=0;
             }*/
        }
    }



    for (i = 1; i < 10; i++)
    {
        SDL_FreeSurface(animation[i]);
    }
    for (i=1; i<6; i++)
    {
        SDL_FreeSurface(boutonsA[i]);
        SDL_FreeSurface(boutonsB[i]);
    }

    SDL_FreeSurface(options_back);
    for (i = 0; i < 8; i++)
    {
        SDL_FreeSurface(options[i]);
    }
    Mix_PauseMusic();
    Mix_FreeMusic(musique);

    menu.done=1;

    if (menu.etat==5)
        return -1;

    return 0;
}
