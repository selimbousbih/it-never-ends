/**

* @file functions.c

* @author C Squad

* @version 1.0

* @date May 14, 2016

*/


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "game.h"
#include "functions.h"

void init_items(GAME *game);

void init_input(GAME *game)
{
    game->input.right=0;
    game->input.left=0;
    game->input.up=0;
    game->input.down=0;
    game->input.fix=0;
    game->input.enter=0;
    game->input.startJump=0;
    game->input.jumpHeight=0;

    game->arduino.right=0;
    game->arduino.left=0;
    game->arduino.up=0;
}

void init_characters(GAME *game)
{

    /* character principal */
    game->character.position.x=434;
    game->character.position.y=game->config.resolution_h-600;
    game->character.life=3;
    game->character.actuel=0;
    game->character.look=0;
    game->character.pos_cercle.r=30;
    game->character.speed=12;

    /* npc's */
    if (game->level==1)
    {
        game->character.speed=12;

        /* enemy 1*/
        game->npc[0].position.x=2500;
        game->npc[0].position.y=START_Y+465;
        game->npc[0].direction=1;
        game->npc[0].fix=0;
        game->npc[0].life=1;
        game->npc[0].actuel=0;
        game->npc[0].look=0;
        game->npc[0].speed=1;
        game->npc[0].vision_range=350;
        game->npc[0].behavior=PATROL;

        /* officer */
        game->npc[1].position.x=542;
        game->npc[1].position.y=START_Y+465;
        game->npc[1].direction=0;
        game->npc[1].fix=0;
        game->npc[1].life=100;
        game->npc[1].actuel=0;
        game->npc[1].look=0;
        game->npc[1].speed=0;
        game->npc[1].vision_range=0;

        /* enemy 2 & 3 */
        game->npc[2].position.x=4900;
        game->npc[2].position.y=START_Y+465;
        game->npc[2].direction=1;
        game->npc[2].fix=0;
        game->npc[2].life=1;
        game->npc[2].actuel=0;
        game->npc[2].look=0;
        game->npc[2].speed=1;
        game->npc[2].vision_range=330;
        game->npc[2].behavior=PATROL;

        game->npc[3].position.x=5800;
        game->npc[3].position.y=START_Y+465;
        game->npc[3].direction=-1;
        game->npc[3].actuel=1;
        game->npc[3].look=2;
        game->npc[3].speed=1;
        game->npc[3].vision_range=330;
        game->npc[3].behavior=PATROL;

        game->character.position.y+=300;
    }
    else if (game->level==2)
    {
        game->npc[4].position.x=8280;
        game->npc[4].position.y=START_Y+400;
        game->npc[4].direction=1;
        game->npc[4].actuel=0;
        game->npc[4].look=2;
        game->npc[4].speed=0;
        game->npc[4].vision_range=350;
        game->npc[4].behavior=REFRACT;
        game->character.speed=16;
    }
     else  if (game->level==3)
       {
         game->character.position.x=850;
          game->character.position.y+=200;
          game->character.speed=10;
       }

    else if (game->level==4)
        {
            game->character.position.x=game->config.resolution_w/2-120;
            game->character.speed=12;
        }


}

void init_global_vars(GAME *game)
{
    int i=0;
    game->global.EOL=0;
    game->gui.pos_dialogue.x=(game->config.resolution_w-game->gui.dialogue[0]->w)/2;
    game->gui.pos_dialogue.y=90;
    game->gui.pos_btn.x=(game->config.resolution_w-game->gui.dialogue[0]->w)/2 + 900;
    game->gui.pos_btn.y=580;

    game->background.pos_rain.h=PLAT_H;
    game->background.pos_rain.w=PLAT_W;
    game->background.pos_rain.x=0;
    game->background.pos_rain.y=0;

    game->texte.indice[0]=1;
    game->global.fix=0;
    game->global.stopDisplay=0;

    for (i=0; i<5; i++) //bullet
    {
        game->objects.bullet[i].started=0;
        game->objects.bullet[i].speed=26;
        game->objects.bullet[i].direction=0;
        game->objects.bullet[i].cercle.r=10;
        game->objects.bullet[i].cercle.x=0;
        game->objects.bullet[i].cercle.y=0;
        game->global.get_elapsed_npc[i]=1;

    }


    game->texte.actuel=0;
    game->texte.i=0;

    game->texte.couleur.r = 255;
    game->texte.couleur.g = 255;
    game->texte.couleur.b = 255;

    game->background.scroll_x=0;
    game->background.scroll_y=0;
    game->background.counter=0;

    if (game->level==3)
        game->background.scroll_x=10000-game->config.resolution_w;


    game->gui.show_dialogue=0;
    game->gui.show_inv=0;

    game->character.died=0;

    game->character.pos_cercle.r=30;

    game->global.obj_i=0;
    game->global.show_message=0;
    game->sprite=2;

    game->global.movement=0;
    game->global.on_door=0;
    game->texte.fix=0;

    game->global.FIN=0;
    game->global.fire_i=0;


game->global.fix_died=0;
game->global.frame_died=0;
game->global.on_door=0;


}

void init_private_vars(GAME *game)
{
      int i=0;

    switch(game->level)
    {
    case 1:
        game->global.checkpoint=0;

        game->objects.objective.position.x=8600;
        game->objects.objective.position.y=START_Y+480;
        game->objects.objective.cercle.x=8600;
        game->objects.objective.cercle.y=START_Y+480;
        game->objects.objective.cercle.r=20;


        game->gui.pos_avatar.x=20;
        game->gui.pos_avatar.y=START_Y+15;
        game->gui.pos_hp.x=120;
        game->gui.pos_hp.y=START_Y+110;

        /* borders */
        game->objects.borders.left[0]=0;
        game->objects.borders.right[0]=10000;
        game->objects.borders.left[1]=-1;
        game->objects.borders.right[1]=-1;

		game->objects.inventory.item[0].number=0;
		game->objects.inventory.item[0].have=1;
		game->objects.inventory.item[0].selected=1;
		game->objects.inventory.count=1;

		 game->global.fix_tutorial=0;
		 game->global.on_tutorial=0;


        break;
    case 2:
        game->global.checkpoint=0;

        game->objects.objective.position.x=9340;
        game->objects.objective.position.y=START_Y+460;
        game->objects.objective.cercle.x=9340;
        game->objects.objective.cercle.y=START_Y+460;
        game->objects.objective.cercle.r=40;

        game->gui.pos_avatar.x=25;
        game->gui.pos_avatar.y=100;
        game->gui.pos_hp.x=125;
        game->gui.pos_hp.y=195;

		game->global.level2_show_items=0;

        /* borders */
        game->objects.borders.left[0]=0;
        game->objects.borders.right[0]=4020;

        game->objects.borders.left[1]=4020;
        game->objects.borders.right[1]=5350;

        game->objects.borders.left[2]=5300;
        game->objects.borders.right[2]=6830;

        game->objects.borders.left[3]=6850;
        game->objects.borders.right[3]=8870;

        game->objects.borders.left[4]=9000;
        game->objects.borders.right[4]=10000;
        game->objects.borders.left[5]=-1;
        game->objects.borders.right[5]=-1;

        /*doors*/
        for (i=0;i<5;i++)
        {
            game->objects.door[i].x=game->objects.borders.right[i]-150;
            game->objects.door[i].y=START_Y+460;
            game->objects.door[i].r=120;
        }

        game->objects.door[1].x=5200;



		game->objects.inventory.item[0].number=0;
		game->objects.inventory.item[0].have=0;
		game->objects.inventory.item[0].selected=1;
		game->objects.inventory.count=1;

		game->objects.inventory.item[1].number=0;
		game->objects.inventory.item[1].have=0;
		game->objects.inventory.item[1].selected=0;
		game->objects.inventory.count=1;


		game->objects.inventory.item[2].number=0;
		game->objects.inventory.item[2].have=0;
		game->objects.inventory.item[2].selected=0;
        game->objects.inventory.item[2].cercle.x=2000;
		game->objects.inventory.item[2].cercle.y=START_Y+530;
		game->objects.inventory.item[2].cercle.r=100;
		game->objects.inventory.item[2].disposable=1;


		game->objects.inventory.item[3].number=2;
		game->objects.inventory.item[3].have=0;
		game->objects.inventory.item[3].selected=0;
        game->objects.inventory.item[3].cercle.x=5700;
		game->objects.inventory.item[3].cercle.y=START_Y+530;
		game->objects.inventory.item[3].cercle.r=100;
		game->objects.inventory.item[3].disposable=1;


        break;
    case 3:
        game->global.checkpoint=0;

        game->objects.objective.position.x=294;
        game->objects.objective.position.y=532;
        game->objects.objective.cercle.x=350;
        game->objects.objective.cercle.y=500;
        game->objects.objective.cercle.r=40;

        game->gui.pos_avatar.x=25;
        game->gui.pos_avatar.y=100;
        game->gui.pos_hp.x=125;
        game->gui.pos_hp.y=195;

        /* borders */
        game->objects.borders.left[0]=0;
        game->objects.borders.right[0]=10000;
        game->objects.borders.left[1]=-1;
        game->objects.borders.right[1]=-1;
		game->objects.borders.left[2]=0;
        game->objects.borders.right[2]=10000;
		game->objects.borders.left[3]=0;
        game->objects.borders.right[3]=10000;
		game->objects.borders.left[4]=0;
        game->objects.borders.right[4]=10000;
		game->objects.borders.left[5]=0;
        game->objects.borders.right[5]=10000;

		/* doors */
		game->objects.door[0].x=7600;
        game->objects.door[0].y=START_Y+460;
        game->objects.door[0].r=80;
		game->objects.door[1].x=7162;
		game->objects.door[1].y=START_Y+460;
		game->objects.door[1].r=80;
		game->objects.door[2].x=6300;
		game->objects.door[2].y=START_Y+460;
		game->objects.door[2].r=80;
		game->objects.door[3].x=5690;
		game->objects.door[3].y=START_Y+460;
		game->objects.door[3].r=80;
		game->objects.door[4].x=5265;
		game->objects.door[4].y=START_Y+460;
		game->objects.door[4].r=80;
		game->objects.door[5].x=4825;
		game->objects.door[5].y=START_Y+460;
		game->objects.door[5].r=80;
		game->objects.door[6].x=4185;
		game->objects.door[6].y=START_Y+460;
		game->objects.door[6].r=80;
		game->objects.door[7].x=3310;
		game->objects.door[7].y=START_Y+460;
		game->objects.door[7].r=80;
		game->objects.door[8].x=2711;
		game->objects.door[8].y=START_Y+460;
		game->objects.door[8].r=80;
		game->objects.door[9].x=2291;
		game->objects.door[9].y=START_Y+460;
		game->objects.door[9].r=80;
		game->objects.door[10].x=1835;
		game->objects.door[10].y=START_Y+460;
		game->objects.door[10].r=80;

		/* coin */
		game->objects.inventory.item[1].number=0;
		game->objects.inventory.item[1].cercle.x=9400;
		game->objects.inventory.item[1].cercle.y=START_Y+530;
		game->objects.inventory.item[1].cercle.r=100;
		game->objects.inventory.item[1].have=0;
		game->objects.inventory.item[1].disposable=1;



        break;

    case 4:
        game->global.checkpoint=0;

        game->objects.objective.position.x=9850;
        game->objects.objective.position.y=START_Y+460;;
        game->objects.objective.cercle.x=9600;
        game->objects.objective.cercle.y=START_Y+460;;
        game->objects.objective.cercle.r=60;

        game->gui.pos_avatar.x=25;
        game->gui.pos_avatar.y=100;
        game->gui.pos_hp.x=125;
        game->gui.pos_hp.y=195;

        /* borders */
        game->objects.borders.left[0]=8000;
        game->objects.borders.right[0]=10000;
        game->objects.borders.left[1]=-1;
        game->objects.borders.right[1]=-1;

        break;
    }
}
void init_variables(GAME *game)
{
  init_global_vars(game);
  init_private_vars(game);

}


void load_images(GAME *game)
{
    int i=0;	char died[30]=" ";
    for (i=0; i<5; i++)
        game->npc[i].image=NULL;

    game->gui.avatar=IMG_Load("DATA/GFX/GUI/Avatar.png");

    game->gui.btn_animated[0]=IMG_Load("DATA/GFX/GUI/up.png");
    game->gui.btn_animated[1]=IMG_Load("DATA/GFX/GUI/down.png");

    game->gui.inventaire=IMG_Load("DATA/GFX/inventory/inventory.png");
	game->gui.frame=IMG_Load("DATA/GFX/inventory/frame.png");

    if (game->level==1)
        game->character.image=IMG_Load("DATA/GFX/spritesheets/john_level1.png");
    else
        game->character.image=IMG_Load("DATA/GFX/spritesheets/sprites2.png");

	for (i=1;i<33;i++)
	{
		sprintf(died,"DATA/GFX/WASTED/%d.png",i);
		game->gui.died[i]=IMG_Load(died);
	}



    switch (game->level)
    {
    case 1:
        game->gui.dialogue[0]=IMG_Load("DATA/GFX/GUI/Dialogue_JOHN.png");
        game->gui.dialogue[1]=IMG_Load("DATA/GFX/GUI/Dialogue_POLICE.png");

        game->background.image[0]=IMG_Load("DATA/GFX/Levels/Level1-1.png");
        game->background.image[1]=IMG_Load("DATA/GFX/Levels/Level1-2.png");
        game->background.image[2]=IMG_Load("DATA/GFX/Levels/rain-1.png");
        game->background.image[3]=IMG_Load("DATA/GFX/Levels/rain-2.png");
        game->background.image[4]=IMG_Load("DATA/GFX/Levels/rain-3.png");
        game->background.levelCollision=IMG_Load("DATA/GFX/Levels/Level1-Collision.png");

        game->npc[0].image=IMG_Load("DATA/GFX/spritesheets/bad_guy1.png");
        game->npc[1].image=IMG_Load("DATA/GFX/spritesheets/police.png");
        game->npc[2].image=IMG_Load("DATA/GFX/spritesheets/bad_guy1.png");
        game->npc[3].image=IMG_Load("DATA/GFX/spritesheets/bad_guy1.png");

        game->objects.tutorial[0]=IMG_Load("DATA/GFX/tutorial/frame.png");
        for (i=1;i<9;i++)
        {
            sprintf(died,"DATA/GFX/tutorial/%d.bmp",i);
            game->objects.tutorial[i]=IMG_Load(died);
        }
        game->objects.pos_tuto.x=game->config.resolution_w/2-150;
        game->objects.pos_tuto.y=game->config.resolution_h/2-150;

        break;

    case 2:
        game->gui.dialogue[0]=IMG_Load("DATA/GFX/GUI/Dialogue_JOHN.png");
        game->gui.dialogue[1]=IMG_Load("DATA/GFX/GUI/Dialogue_BARMAN.png");
        game->gui.dialogue[2]=IMG_Load("DATA/GFX/GUI/Dialogue_WADE.png");

        game->npc[4].image=IMG_Load("DATA/GFX/spritesheets/jazzar1.png");

        game->background.image[0]=IMG_Load("DATA/GFX/Levels/Level2-1.png");
        game->background.image[1]=IMG_Load("DATA/GFX/Levels/Level2-2.png");
        game->background.image[2]=IMG_Load("DATA/GFX/Levels/All Items.png");
        game->background.levelCollision=IMG_Load("DATA/GFX/Levels/Level2-Collision.png");
        break;

    case 3:
        game->gui.dialogue[0]=IMG_Load("DATA/GFX/GUI/Dialogue_JOHN.png");
        //game->gui.dialogue[1]=IMG_Load("DATA/GFX/GUI/Dialogue_POLICE.png");

        game->background.image[0]=IMG_Load("DATA/GFX/Levels/Level3-1.png");
        game->background.image[1]=IMG_Load("DATA/GFX/Levels/Level3-2.png");
        game->background.levelCollision=IMG_Load("DATA/GFX/Levels/Level3-Collision.png");
        break;


    case 4:

        game->gui.dialogue[0]=IMG_Load("DATA/GFX/GUI/Dialogue_JOHN.png");

        game->background.image[0]=IMG_Load("DATA/GFX/Levels/Level4.png");
        game->background.image[1]=IMG_Load("DATA/GFX/Fire/1.png");
        game->background.image[2]=IMG_Load("DATA/GFX/Fire/2.png");
        game->background.image[3]=IMG_Load("DATA/GFX/Fire/3.png");
        game->background.image[4]=IMG_Load("DATA/GFX/Fire/4.png");
        game->background.image[5]=IMG_Load("DATA/GFX/Fire/5.png");
        game->background.levelCollision=IMG_Load("DATA/GFX/Levels/Level4-Collision.png");
        break;
    }


    for (i=0; i<5; i++)
        game->objects.bullet[i].image=IMG_Load("DATA/GFX/spritesheets/bullet.png");

    game->objects.objective.image=IMG_Load("DATA/GFX/spritesheets/objective.png");

}

void init_level(GAME *game)
{
    init_input(game);
    load_images(game);
	init_items(game);
    init_variables(game);
    init_characters(game);


    game->texte.police = TTF_OpenFont("DATA/fonts/FSEX300.ttf", 24);

    char dlg[25]=" ";
    sprintf(dlg,"DATA/texte/level%d.dlg",game->level);
    game->texte.f=fopen(dlg,"r");


    SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 0, 0, 0));
    loading_screen(game);

}

/* Fin Initialisation */

void loading_screen(GAME *game)
{

    SDL_Surface *loading[4];
    SDL_Rect position_src= {PLAT_H,PLAT_W,0,0}, position_dst= {PLAT_H,PLAT_W,0,0};

    position_dst.y=0;
    position_dst.x=(game->config.resolution_w-1167)/2;

    position_src.y=PLAT_H;
    position_src.x=0;
    position_src.h=600;
    position_src.w=1167;

    int i=0, j=0;

    loading[0]=IMG_Load("DATA/GFX/loading screen/Boss_before.jpg");
    loading[1]=IMG_Load("DATA/GFX/loading screen/Boss_after.jpg");
    loading[2]=IMG_Load("DATA/GFX/loading screen/Wade_before.jpg");
    loading[3]=IMG_Load("DATA/GFX/loading screen/Wade_after.jpg");

    j=(rand()%2)*2;
    SDL_BlitSurface(loading[j],NULL,game->screen,&position_dst);

    while(position_src.y>0)
    {
        position_src.y-=rand()%6;
        position_src.h=game->config.resolution_h-position_src.y;
        position_dst.y=position_src.y;
        if (position_src.y<0)
            position_src.y=0;

        SDL_BlitSurface(loading[j+1],&position_src,game->screen,&position_dst);
        SDL_Flip(game->screen);
    }

    for (i=0; i<4; i++)
        SDL_FreeSurface(loading[i]);


}

void blit_text(GAME *game)
{
    if (!game->texte.fix)
    {
        game->texte.couleur.r = 255;
        game->texte.couleur.g = 255;
        game->texte.couleur.b = 255;

        game->gui.pos_dialogue.x=(game->config.resolution_w-game->gui.dialogue[0]->w)/2;
        game->gui.pos_dialogue.y=90;

        game->gui.pos_btn.x=(game->config.resolution_w-game->gui.dialogue[0]->w)/2 + 900;
        game->gui.pos_btn.y=580;

        game->texte.position.x = (game->config.resolution_w-game->gui.dialogue[0]->w)/2+50;
        game->texte.position.y = 500;
        game->texte.i=0;

        game->texte=dialogue_lines(game->texte);
        game->texte.fix=1;

    }
    game->texte.texte = TTF_RenderText_Solid(game->texte.police, game->texte.dialogue[game->texte.i], game->texte.couleur);
    SDL_BlitSurface(game->texte.texte, NULL, game->screen, &game->texte.position);
    game->texte.texte = TTF_RenderText_Solid(game->texte.police, game->texte.dialogue[game->texte.i+1], game->texte.couleur);
    game->texte.position.y+=50;
    SDL_BlitSurface(game->texte.texte, NULL, game->screen, &game->texte.position);
    game->texte.position.y-=50;

    SDL_Flip(game->screen);

}

Texte dialogue_lines(Texte texte)
{
    int i=0,j=0, lines=0,n=0;
    char c=' ';
    rewind(texte.f);
    while (i!=texte.actuel)
    {
        while(c!='[')
        {
            c=fgetc(texte.f);
        }
        if (c=='[')
        {
            fscanf(texte.f,"%d]\n",&i);
            c=fgetc(texte.f);
        }
    }
    n=ftell(texte.f)-1;

    if (i==texte.actuel)
    {
        c=' ';
        while(c!='[')
        {
            c=fgetc(texte.f);
            if (c=='\n')
                lines++;
        }

    }
    //fprintf(stderr,"%d",n);
    fseek(texte.f,n,SEEK_SET);
    i=0;
    //lines/=2;
    while(j<lines/2)
    {
        strcpy(texte.aux," ");
        fscanf(texte.f,"%d\n",&texte.indice[j]);
        texte.indice[j+1]=texte.indice[j];

        fgets(texte.aux,100,texte.f);
        texte.aux[strlen(texte.aux+1)]='\0';
        strcpy(texte.dialogue[j],texte.aux);

        strcpy(texte.aux," ");
        fgets(texte.aux,100,texte.f);
        texte.aux[strlen(texte.aux+1)]='\0';
        strcpy(texte.dialogue[j+1],texte.aux);
        j+=2;
    }
    texte.line=lines;
    return (texte);
}


int SDL_TICKS_PASSED(unsigned int A, unsigned int B)
{
    return(SDL_GetTicks()-A>=B);
}


void load_music(GAME *game)
{
    char file[50]=" ";

    sprintf(file,"DATA/SFX/level%d.mp3",game->level);
    game->musique.ambient = Mix_LoadMUS(file);

}

void play_music(Music *musique)
{
    Mix_PlayMusic(musique->ambient, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME/5);
}

void free_memory(GAME *game)
{
    int i=0;

/*    for(i=0;i<5;i++)
        if (game->background.image[i]!=NULL)
            SDL_FreeSurface(game->background.image[i]);
*/
    SDL_FreeSurface(game->background.levelCollision);


    SDL_FreeSurface(game->character.image);
    SDL_FreeSurface(game->gui.avatar);
    SDL_FreeSurface(game->gui.hp);
    SDL_FreeSurface(game->gui.inventaire);

    for (i=0;i<2;i++)
    {
        //SDL_FreeSurface(game->gui.btn_animated[0]);
        SDL_FreeSurface(game->gui.btn_animated[i]);
    }


    for (i=0;i<2;i++)
    {
        if (game->gui.dialogue[i]!=NULL)
            SDL_FreeSurface(game->gui.dialogue[i]);
    }



	for (i=1;i<33;i++)
    {
        if (game->gui.died[i]!=NULL)
            SDL_FreeSurface(game->gui.died[i]);
    }




    for (i=0; i<5; i++)
        if (game->npc[i].image!=NULL)
            SDL_FreeSurface(game->npc[i].image);

     for (i=0; i<5; i++)
        if (game->objects.bullet[i].image!=NULL)
             SDL_FreeSurface(game->objects.bullet[i].image);

    Mix_FreeMusic(game->musique.ambient);

}

int center_camera(GAME *game)
{
    return (game->character.position.x+32>game->config.resolution_w/2 && game->character.position.x-32<game->config.resolution_w/2);
}

int random_case(GAME *game)
{
    return(((game->background.counter>20) && (game->background.counter <24)) || ((game->background.counter>25)&&(game->background.counter<29)) || ((game->background.counter>46) && (game->background.counter <50)) || ((game->background.counter>51)&&(game->background.counter<55)) || ((game->background.counter>56)&&(game->background.counter<60)) || ((game->background.counter>96)&&(game->background.counter<100)));
}

char *tostr(int x)
{
    char *ch=(char*)malloc(3*sizeof(char));
    sprintf(ch,"%d",x);
    return ch;
}

int relative_x(GAME *game, SDL_Rect position)
{
    return (position.x-game->background.scroll_x);
}
