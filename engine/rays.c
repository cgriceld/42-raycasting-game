#include "maze.h"

static void boarders_wall(int *start, int *end, int *height, t_game *game)
{
	*height = (int)(game->res[Y] / game->perpwalldist);
	*start =  game->res[Y] / 2 - *height / 2;
	*end = game->res[Y] / 2 + *height / 2;
	*start = *start < 0 ? 0 : *start;
	*end = *end >= game->res[Y] ? game->res[Y] - 1 : *end;
}

static void draw_slice(t_mlximg *wall, t_game *game, int ray)
{
	int height;
	int start;
	int end;
	int	hit_ttrX;
	double	where_hit;
	double step;
	double hit_ttrY;

	boarders_wall(&start, &end, &height, game);
	where_hit = !game->side ? game->pos[Y] + game->perpwalldist * game->raydir[Y] : \
	game->pos[X] + game->perpwalldist * game->raydir[X];
	where_hit -= floor((where_hit));
	hit_ttrX = (int)(where_hit * (double)(wall->img_width));
	if ((!game->side && game->raydir[X] > 0) || \
		(game->side && game->raydir[Y] < 0))
		hit_ttrX = wall->img_width - hit_ttrX - 1;
	step = 1.0 * wall->img_height / height;
	while (start < end)
	{
		hit_ttrY = (256 * start - 128 * game->res[Y] + 128 * height) * step / 256;
		game->maze->data[game->maze->img_width * start + ray] = \
		wall->data[(int)hit_ttrY * wall->img_width + hit_ttrX];
		start++;
	}
}

static t_mlximg *get_slice(t_game *game, int ray)
{
	t_mlximg	*wall;

	game->perpwalldist = !game->side ? \
	(game->square[X] - game->pos[X] + (1 - game->step[X]) / 2) / \
	game->raydir[X] : \
	(game->square[Y] - game->pos[Y] + (1 - game->step[Y]) / 2) / \
	game->raydir[Y];
	game->zbuffer[ray] = game->perpwalldist;
	if (game->raydir[X] > 0 && game->raydir[Y] >= 0)
		wall = !game->side ? game->ttrs[EA] : game->ttrs[SO];
	if (game->raydir[X] > 0 && game->raydir[Y] < 0)
		wall = !game->side ? game->ttrs[EA] : game->ttrs[NO];
	if (game->raydir[X] <= 0 && game->raydir[Y] < 0)
		wall = !game->side ? game->ttrs[WE] : game->ttrs[NO];
	if (game->raydir[X] <= 0 && game->raydir[Y] >= 0)
		wall = !game->side ? game->ttrs[WE] : game->ttrs[SO];
	return (wall);
}

static void	find_wall(t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{

		if (game->sidedist[Y] < game->sidedist[X])
		{
			game->sidedist[Y] += game->deltadist[Y];
			game->square[Y] += game->step[Y];
			game->side = 1;
		}
		else if (game->sidedist[X] < game->sidedist[Y])
		{
			game->sidedist[X] += game->deltadist[X];
			game->square[X] += game->step[X];
			game->side = 0;
		}
		if (game->map[game->square[Y]][game->square[X]] == '1')
			hit++;
	}
}

void		throw_rays(t_game *game)
{
	int ray;
	
	ray = 0;
	while (ray < game->res[X])
	{
		game->square[X] = (int)game->pos[X];
		game->square[Y] = (int)game->pos[Y];
		game->camerax = 2 * ray / (double)(game->res[X]) - 1;
		game->raydir[X] = game->dir[X] + game->plane[X] * game->camerax;
		game->raydir[Y] = game->dir[Y] + game->plane[Y] * game->camerax;
		game->deltadist[X] = fabs(1 / game->raydir[X]);
		game->deltadist[Y] = fabs(1 / game->raydir[Y]);
		game->step[X] = game->raydir[X] > 0 ? 1 : -1;
		game->sidedist[X] = game->raydir[X] > 0 ? \
		(1.0 - (game->pos[X] - game->square[X])) * game->deltadist[X] : \
		(game->pos[X] - game->square[X]) * game->deltadist[X];
		game->step[Y] = game->raydir[Y] > 0 ? 1 : -1;
		game->sidedist[Y] = game->raydir[Y] > 0 ? \
		(1.0 - (game->pos[Y] - game->square[Y])) * game->deltadist[Y] : \
		(game->pos[Y] - game->square[Y]) * game->deltadist[Y];
		find_wall(game);
		draw_slice(get_slice(game, ray), game, ray);
		ray++;
	}
}
