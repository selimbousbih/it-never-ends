#include "game.h"

/**

* @file items.c

* @author C Squad

* @version 1.0

* @date May 14, 2016

*/

void inventory_options(GAME *game);
int fix_inv=0;

void init_items(GAME *game)
{
	int i=0;
	char item[40]=" ";
	game->objects.inventory.count=0;
	for (i=0;i<MAX_ITEMS;i++)
	{
		game->objects.inventory.item[i].number=0;
		game->objects.inventory.item[i].have=0;
		game->objects.inventory.item[i].disposable=0;
		game->objects.inventory.item[i].position.x=0;
		game->objects.inventory.item[i].position.y=0;
		sprintf(item,"DATA/GFX/inventory/item%d.png",i);
		game->objects.inventory.item[i].image=IMG_Load(item);
		sprintf(item,"DATA/GFX/inventory/description%d.png",i);
		game->objects.inventory.item[i].description=IMG_Load(item);
	}
}
int pick_item(GAME *game)
{
	int i=0;
	for (i=0;i<MAX_ITEMS;i++)
	{
		if (collision_cercle(game->character.pos_cercle, game->objects.inventory.item[i].cercle))
		{
			if (game->objects.inventory.item[i].have==0)
			{
				if (game->objects.inventory.item[i].disposable)
				{
					//game->objects.inventory.item[i].number=0;//game->objects.inventory.count;
					game->objects.inventory.count++;
					game->objects.inventory.item[i].have=1;
                    game->objects.inventory.item[i].selected=0;
                    return 1;
				}
			}

		}

	}
	return 0;

}

void drop_item(GAME *game)
{
int i=0;
for (i=0;i<MAX_ITEMS;i++)
	{
		if (game->objects.inventory.item[i].have==1)
		{
			if (game->objects.inventory.item[i].selected)
				{
					if (game->objects.inventory.item[i].disposable)
					{
						game->objects.inventory.item[i].cercle.x=TRUE_X;//+game->character.direction*50;
						game->objects.inventory.item[i].have=0;
                        game->objects.inventory.item[i].selected=0;
					}
				}
		}

	}

}

void show_inventory(GAME *game)
{
	int i=0;

	game->gui.pos_inv.x=game->character.position.x+30;
	game->gui.pos_inv.y=game->character.position.y-90;

	SDL_BlitSurface(game->gui.inventaire, NULL, game->screen, &game->gui.pos_inv);

	for (i=0;i<MAX_ITEMS;i++)
	{
		if (game->objects.inventory.item[i].have==1)
		{
			game->objects.inventory.item[i].position.y=game->gui.pos_inv.y+5;
			game->objects.inventory.item[i].position.x=game->gui.pos_inv.x+game->objects.inventory.item[i].number*42+6+game->objects.inventory.item[i].number*5;
			SDL_BlitSurface(game->objects.inventory.item[i].image, NULL, game->screen, &game->objects.inventory.item[i].position);
			if (game->objects.inventory.item[i].selected==1)
			{
				//game->objects.inventory.item[i].position.x+=game->objects.inventory.item[i].number*5;
				SDL_BlitSurface(game->gui.frame, NULL, game->screen, &game->objects.inventory.item[i].position);
				game->objects.inventory.item[i].position.y=game->gui.pos_inv.y-game->objects.inventory.item[i].description->h-20;
				game->objects.inventory.item[i].position.x=game->gui.pos_inv.x;
				SDL_BlitSurface(game->objects.inventory.item[i].description, NULL, game->screen, &game->objects.inventory.item[i].position);

			}

		}

	}
if (game->level==3)
game->objects.inventory.item[0].selected=1;
inventory_options(game);
}

void inventory_options(GAME *game)
{
int i=0;

	            if (game->input.right && !fix_inv)
	            {
					fix_inv=1;
	                for (i=0;i<MAX_ITEMS-1;i++)
					{
						if (game->objects.inventory.item[i].selected)
						{
							game->objects.inventory.item[i].selected=0;
							game->objects.inventory.item[i+1].selected=1;
                            break;
						}
					}
                }

	             if (game->input.left && !fix_inv)
	            {
	                for (i=1;i<MAX_ITEMS;i++)
					{
						if (game->objects.inventory.item[i].selected)
						{
							game->objects.inventory.item[i].selected=0;
							game->objects.inventory.item[i-1].selected=1;
							break;
						}
					}
                }

				if (game->input.right==0 && game->input.left==0)
					fix_inv=0;


}
