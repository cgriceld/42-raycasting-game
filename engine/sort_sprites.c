#include "maze.h"

static void	swap_coord(double *spr1, double *spr2, int pos, double **sprites)
{
	double tmp;
	double tmpx;
	double tmpy;

	tmp = *spr1;
	*spr1 = *spr2;
	*spr2 = tmp;
	tmpx = sprites[pos][X];
	tmpy = sprites[pos][Y];
	sprites[pos][X] = sprites[pos + 1][X];
	sprites[pos][Y] = sprites[pos + 1][Y];
	sprites[pos + 1][X] = tmpx;
	sprites[pos + 1][Y] = tmpy;
}

void		sort_sprites(t_game *game)
{
	double	*far;
	int		num;
	int		pos;

	far = (double *)malloc(sizeof(double) * game->numspr);
	if (!far)
		game_error(MLX_MALLOC, &game);
	num = game->numspr;
	while (num--)
		far[num] = (game->player[X] - game->sprites[num][X]) \
		* (game->player[X] - game->sprites[num][X]) \
		+ (game->player[Y] - game->sprites[num][Y]) \
		* (game->player[Y] - game->sprites[num][Y]);
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
