#include "maze.h"

/*
** From farest to nearest
*/
static void	swap_coord(double *spr1, double *spr2, int pos, double **sprites)
{
	double tmp;
	double tmpX;
	double tmpY;

	tmp = *spr1;
	*spr1 = *spr2;
	*spr2 = tmp;
	tmpX = sprites[pos][X];
	tmpY = sprites[pos][Y];
	sprites[pos][X] = sprites[pos + 1][X];
	sprites[pos][Y] = sprites[pos + 1][Y];
	sprites[pos + 1][X] = tmpX;
	sprites[pos + 1][Y] = tmpY;
}

void		sort_sprites(t_game *game)
{
	double	*far;
	int		num;
	int		pos;

	far = (double *)malloc(sizeof(double) * game->numspr);
	if (!far)
		game_error(MALLOC_GAME, &game);
	num = game->numspr;
	while (num--)
		far[num] = (game->pos[X] - game->sprites[num][X]) \
		* (game->pos[X] - game->sprites[num][X]) \
		+ (game->pos[Y] - game->sprites[num][Y]) \
		* (game->pos[Y] - game->sprites[num][Y]);
	num = game->numspr;
	while (num--)
	{
		pos = 0;
		while (pos < num)
		{
			if (far[pos] < far[pos + 1])
				swap_coord(&far[pos], &far[pos + 1], pos, game->sprites);
			pos++;
		}
	}
	free(far);
}