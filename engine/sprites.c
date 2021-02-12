#include "maze.h"

static void boarders_sprite(t_game *game, int *start, int *end)
{
	start[Y] = -game->spr->spriteh / 2 + game->res[Y] / 2;
	start[Y] = start[Y] < 0 ? 0 : start[Y];
	end[Y] = game->spr->spriteh / 2 + game->res[Y] / 2;
	end[Y] = end[Y] >= game->res[Y] ? game->res[Y] - 1 : end[Y];
	start[X] = -game->spr->spritew / 2 + game->spr->spritescreenx;
	start[X] = start[X] < 0 ? 0 : start[X];
	end[X] = game->spr->spritew / 2 + game->spr->spritescreenx;
	end[X] = end[X] >= game->res[X] ? game->res[X] - 1 : end[X];
}

static void y_loop(t_game *game, int stripeY, int hitX, int x)
{
	double stepH;
	double hitY;
	int pxl;

	stepH = 1.0 * game->ttrs[SPRITE]->img_height / game->spr->spriteh;
	hitY = (256 * stripeY - 128 * game->res[Y] + 128 * game->spr->spriteh) * stepH / 256;
	pxl = game->ttrs[SPRITE]->data[game->ttrs[SPRITE]->img_width * (int)hitY + hitX];
	if (pxl & NO_TRANSPARENT)
		game->maze->data[stripeY * game->maze->img_width + x] = pxl;
}

static void draw_stripes(t_game *game, double transformy)
{
	double		hitX;
	int stripeY;
	int start[2];
	int end[2];
	double stepW;

	boarders_sprite(game, start, end);
	stepW = 1.0 * game->ttrs[SPRITE]->img_width / game->spr->spritew;
	while (start[X] < end[X])
	{
		hitX = (256 * start[X] + 128 * game->spr->spritew - 256 * game->spr->spritescreenx) * stepW / 256;
		if (transformy > 0 && start[X] > 0 && start[X] < game->res[X] && \
			transformy < game->zbuffer[start[X]])
		{
			stripeY = start[Y];
			while (stripeY < end[Y])
			{
				y_loop(game, stripeY, (int)hitX, start[X]);
				stripeY++;
			}
		}
		start[X]++;
	}
}

void	sprites(t_game *game)
{
	int		tmp;
	double	sprite[2];
	double	invdet;
	double	transform[2];

	tmp = 0;
	while (tmp < game->numspr)
	{
		sprite[X] = game->sprites[tmp][X] - game->pos[X];
		sprite[Y] = game->sprites[tmp][Y] - game->pos[Y];
		invdet = 1.0 / (game->plane[X] * game->dir[Y] - game->dir[X] * game->plane[Y]);
		transform[X] = invdet * (game->dir[Y] * sprite[X] - game->dir[X] * sprite[Y]);
		transform[Y] = invdet * (-game->plane[Y] * sprite[X] + game->plane[X] * sprite[Y]);
		game->spr->spritescreenx = (int)((game->res[X] / 2) * (1 + transform[X] / transform[Y]));
		game->spr->spriteh = abs((int)(game->res[Y] / transform[Y]));
		game->spr->spritew = abs((int)(game->res[Y] / transform[Y]));
		draw_stripes(game, transform[Y]);
		tmp++;
	}
}