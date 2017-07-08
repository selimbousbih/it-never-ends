#include "game.h"
#include "functions.h"

/**

* @file mouvement.c

* @brief It never ends

* @author C Squad

* @version 1.0

* @date May 14, 2016

* player movement and camera management.

*/

int center_camera(GAME *game);
void update_screen(GAME *game);
int Collision_PPP(GAME *game, Character perso);

int borders_test(GAME *game)
{
    printf("a");
    int j=0;

    if (game->input.right || game->arduino.right)
    {
      while (game->objects.borders.left[j]!= -1)
      {
            if (TRUE_X > game->objects.borders.left[j] && TRUE_X < game->objects.borders.right[j])
                    return (game->background.scroll_x+game->config.resolution_w > game->objects.borders.right[j]);
            else
                    j++;

      }
        return 0;
    }

}

void movement(GAME *game)
{
        /* Right */

        if ((game->input.right || game->arduino.right) && !Collision_PPP(game,game->character))
        {
            game->background.scroll_x+=SPEED;
            if (borders_test(game))//game->background.scroll_x > game->background.image[0]->w-game->config.resolution_w)
            {
                game->background.scroll_x-=SPEED;
                game->character.position.x+=SPEED;
                if (game->character.position.x>game->config.resolution_w-game->character.position.w)
                    game->character.position.x-=SPEED;
            }

            if (!center_camera(game))
            {
                if (game->character.position.x<game->config.resolution_w/2)
                {
                    game->character.position.x+=SPEED;
                    game->background.scroll_x-=SPEED;
                }
            }


            if (game->character.look>5)
            {
                game->character.look=0;
                game->character.actuel=0;
            }

            game->character.actuel++;
            if (game->character.actuel>5)
            {
                game->character.actuel=0;
                game->character.look++;
            }
            if (game->character.look>3)
                game->character.look=0;

            game->global.movement=0;
        }

        /* Left */

        else if ((game->input.left || game->arduino.left) && !Collision_PPP(game,game->character))
        {
            game->background.scroll_x-=SPEED;
            if (game->background.scroll_x<0)
            {
                game->background.scroll_x+=SPEED;
                game->character.position.x-=SPEED;
                if (game->character.position.x<0)
                    game->character.position.x+=SPEED;
            }

            if (!center_camera(game))
            {
                if (game->character.position.x>game->config.resolution_w/2)
                {
                    game->character.position.x-=SPEED;
                    game->background.scroll_x+=SPEED;
                }
            }
            if (game->character.look<5)
            {
                game->character.look=5;
                game->character.actuel=5;
            }

            game->character.actuel--;
            if (game->character.actuel<1)
            {
                game->character.actuel=5;
                game->character.look++;
            }
            if (game->character.look>8)
                game->character.look=4;


            game->global.movement=1;

        }

        else// if (!collision_pente(game))
        {
            if (game->global.movement==0)
            {
                game->character.look=4;
                game->character.actuel=0;
            }
            else
            {
                game->character.look=9;
                game->character.actuel=5;
            }
        }

        if ((game->input.up || game->arduino.up) && !game->input.fix)
        {
            game->input.startJump = 1;
        }

        /* JUMP START */

        if (game->input.startJump)
        {
            game->input.fix=1;

            if (game->input.jumpHeight < maxJmpH)
            {
                game->input.jumpHeight += JUMP_POWER;
                game->character.position.y -= JUMP_POWER + 2*GRAVITY;
            }
            else
            {
                game->input.startJump=0;
                game->input.jumpHeight=0;
            }
        }

        /* JUMP END */



        /* GRAVITY */
        game->character.position.y+=GRAVITY;

        if (onGround(game, game->character))
        {
            game->character.position.y-=GRAVITY;
            game->input.fix=0;
        }

        game->character.position.y+=GRAVITY;

        if (onGround(game, game->character))
        {
            game->character.position.y-=GRAVITY;
            game->input.fix=0;
        }



    game->character.pos_cercle.x=game->character.position.x+game->background.scroll_x;
    game->character.pos_cercle.y=game->character.position.y+40;
    game->character.pos_cercle.r=30;

}


void mouvement_level4(GAME *game)
{
    int JMP_POWER=16;

    if (!Collision_PPP(game,game->character))
    {
        game->background.scroll_x+=SPEED;
        if (game->background.scroll_x>10000-game->config.resolution_w)
        {
            game->background.scroll_x-=SPEED;
            game->character.position.x+=SPEED;
        }
    }

    else
    {
        game->background.scroll_x+=SPEED;
        game->character.position.x-=SPEED;
    }


            if (game->character.look>5)
            {
                game->character.look=0;
                game->character.actuel=0;
            }

            game->character.actuel++;
            if (game->character.actuel>5)
            {
                game->character.actuel=0;
                game->character.look++;
            }
            if (game->character.look>3)
                game->character.look=0;

        /* JUMP START */

        if (game->input.up && !game->input.fix)
        {
            game->input.startJump = 1;
        }

        if (game->input.startJump)
        {
            game->input.fix=1;

            if (game->input.jumpHeight < 160) //MAX_JmpH
            {
                game->input.jumpHeight += JMP_POWER; //var
                game->character.position.y -= JMP_POWER + 2*GRAVITY;
            }
            else
            {
                game->input.startJump=0;
                game->input.jumpHeight=0;
            }
        }

        /* JUMP END */



        /* GRAVITY */
        game->character.position.y+=GRAVITY;

        if (onGround(game, game->character))
        {
            game->character.position.y-=GRAVITY;
            game->input.fix=0;
        }

        game->character.position.y+=GRAVITY;

        if (onGround(game, game->character))
        {
            game->character.position.y-=GRAVITY;
            game->input.fix=0;
        }

    if (collision_pente(game) && game->input.right)
        {
            game->character.position.y-=5;
            //game->character.position.x+=SPEED;
        }


game->character.pos_cercle.x=TRUE_X;
game->character.pos_cercle.y=game->character.position.y+game->character.position.h/2;
}


void movement_level3(GAME *game)
{
	if (game->background.scroll_x>7600)
	{
        if (game->input.right && !Collision_PPP(game,game->character))
        {
            game->background.scroll_x+=SPEED;
            if (borders_test(game))
            {
                game->background.scroll_x-=SPEED;
                game->character.position.x+=SPEED;
                if (game->character.position.x>game->config.resolution_w-game->character.position.w)
                    game->character.position.x-=SPEED;
            }

            if (!center_camera(game))
            {
                if (game->character.position.x<game->config.resolution_w/2)
                {
                    game->character.position.x+=SPEED;
                    game->background.scroll_x-=SPEED;
                }
            }


            if (game->character.look>5)
            {
                game->character.look=0;
                game->character.actuel=0;
            }

            game->character.actuel++;
            if (game->character.actuel>5)
            {
                game->character.actuel=0;
                game->character.look++;
            }
            if (game->character.look>3)
                game->character.look=0;

            game->global.movement=0;
        }

        /* ------------------------------------------------------ */

        else if (game->input.left && !Collision_PPP(game,game->character))
        {
            game->background.scroll_x-=SPEED;
            if (game->background.scroll_x<0)
            {
                game->background.scroll_x+=SPEED;
                game->character.position.x-=SPEED;
                if (game->character.position.x<0)
                    game->character.position.x+=SPEED;
            }

            if (!center_camera(game))
            {
                if (game->character.position.x>game->config.resolution_w/2)
                {
                    game->character.position.x-=SPEED;
                    game->background.scroll_x+=SPEED;
                }
            }
            if (game->character.look<5)
            {
                game->character.look=5;
                game->character.actuel=5;
            }

            game->character.actuel--;
            if (game->character.actuel<1)
            {
                game->character.actuel=5;
                game->character.look++;
            }
            if (game->character.look>8)
                game->character.look=4;


            game->global.movement=1;

        }

        else// if (!collision_pente(game))
        {
            if (game->global.movement==0)
            {
                game->character.look=4;
                game->character.actuel=0;
            }
            else
            {
                game->character.look=9;
                game->character.actuel=5;
            }
        }

	}

	else
	{

if (game->input.right && !Collision_PPP(game,game->character))
        {

            game->character.position.x+=SPEED;

            if (game->character.look>5)
            {
                game->character.look=0;
                game->character.actuel=0;
            }

            game->character.actuel++;
            if (game->character.actuel>5)
            {
                game->character.actuel=0;
                game->character.look++;
            }
            if (game->character.look>3)
                game->character.look=0;

            game->global.movement=0;
        }

        /* ------------------------------------------------------ */

        else if (game->input.left && !Collision_PPP(game,game->character))
         {
			 game->character.position.x-=SPEED;


            if (game->character.look<5)
            {
                game->character.look=5;
                game->character.actuel=5;
            }

            game->character.actuel--;
            if (game->character.actuel<1)
            {
                game->character.actuel=5;
                game->character.look++;
            }
            if (game->character.look>8)
                game->character.look=4;


            game->global.movement=1;

        }

        else
        {
            if (game->global.movement==0)
            {
                game->character.look=4;
                game->character.actuel=0;
            }
            else
            {
                game->character.look=9;
                game->character.actuel=5;
            }
        }
	}

        /* GRAVITY */
        game->character.position.y+=GRAVITY;

        if (onGround(game, game->character))
        {
            game->character.position.y-=GRAVITY;
            game->input.fix=0;
        }



    game->character.pos_cercle.x=game->character.position.x+game->background.scroll_x;
    game->character.pos_cercle.y=game->character.position.y+40;
    game->character.pos_cercle.r=30;

}

