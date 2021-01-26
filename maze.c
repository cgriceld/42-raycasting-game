#include "maze.h"

static void step_up(t_game *game)
{
	int pos[2];

	pos[X] = (int)(game->player[X] + (SPEED * game->dir[X]));
	pos[Y] = (int)(game->player[Y] + (SPEED * game->dir[Y]));
	if (game->map[(int)game->player[Y]][pos[X]] != '1' && game->map[pos[Y]][(int)game->player[X]] != '1')
	{
		game->player[X] = pos[X];
		game->player[Y] = pos[Y];
	}
}

static void step_down(t_game *game)
{
	int pos[2];

	pos[X] = (int)(game->player[X] - (SPEED * game->dir[X]));
	pos[Y] = (int)(game->player[Y] - (SPEED * game->dir[Y]));
	if (game->map[(int)game->player[Y]][pos[X]] != '1' && game->map[pos[Y]][(int)game->player[X]] != '1')
	{
		game->player[X] = pos[X];
		game->player[Y] = pos[Y];
	}
}

static void step_left(t_game *game)
{
	int pos[2];

	pos[X] = (int)(game->player[X] - (SPEED * game->plane[X]));
	pos[Y] = (int)(game->player[Y] - (SPEED * game->plane[Y]));
	if (game->map[(int)game->player[Y]][pos[X]] != '1' && game->map[pos[Y]][(int)game->player[X]] != '1')
	{
		game->player[X] = pos[X];
		game->player[Y] = pos[Y];
	}
}

static void step_right(t_game *game)
{
	int pos[2];

	pos[X] = (int)(game->player[X] + (SPEED * game->plane[X]));
	pos[Y] = (int)(game->player[Y] + (SPEED * game->plane[Y]));
	if (game->map[(int)game->player[Y]][pos[X]] != '1' && game->map[pos[Y]][(int)game->player[X]] != '1')
	{
		game->player[X] = pos[X];
		game->player[Y] = pos[Y];
	}
}

static void turn_left(t_game *game)
{
	double prevdirX;
	double prevplaneX;

	prevdirX = game->dir[X];
	prevplaneX = game->plane[X];
	game->dir[X] = game->dir[X] * cos(-SPEED) - game->dir[Y] * sin(-SPEED);
	game->dir[Y] = prevdirX * sin(-SPEED) + game->dir[Y] * cos(-SPEED);
	game->plane[X] = game->plane[X] * cos(-SPEED) - game->plane[Y] * sin(-SPEED);
	game->plane[Y] = prevplaneX * sin(-SPEED) + game->plane[Y] * cos(-SPEED);
}

static void turn_right(t_game *game)
{
	double prevdirX;
	double prevplaneX;

	prevdirX = game->dir[X];
	prevplaneX = game->plane[X];
	game->dir[X] = game->dir[X] * cos(SPEED) - game->dir[Y] * sin(SPEED);
	game->dir[Y] = prevdirX * sin(SPEED) + game->dir[Y] * cos(SPEED);
	game->plane[X] = game->plane[X] * cos(SPEED) - game->plane[Y] * sin(SPEED);
	game->plane[Y] = prevplaneX * sin(SPEED) + game->plane[Y] * cos(SPEED);
}

static void get_img(t_game *game)
{
	game->maze = (t_mlximg *)malloc(sizeof(t_mlximg));
	if (!game->maze)
		game_error(MLX_MALLOC, &game);
	game->maze->img = mlx_new_image(game->mlx, game->res[X], game->res[Y]);
	if (!game->maze->img)
		game_error(MLX_NEWIMG, &game);
	game->maze->data = mlx_get_data_addr(game->maze->img, &game->maze->bits_in_texel, \
						&game->maze->bytes_line, &game->maze->little_endian);
}

static void fc_palette(t_game *game)
{
	char *addr;
	int pixel;

	pixel = -1;
	while (++pixel < game->res[Y] / 2)
	{
		addr = game->maze->data + pixel * game->maze->bytes_line + game->res[X] * (game->maze->bits_in_texel / 8);
		*(unsigned int*)addr = game->colors[CEILING];
	}
	while (++pixel < game->res[Y])
	{
		addr = game->maze->data + pixel * game->maze->bytes_line + game->res[X] * (game->maze->bits_in_texel / 8);
		*(unsigned int*)addr = game->colors[FLOOR];
	}
}

static void raycasting(t_game *game)
{
	int ray;
	int hit;
	int side;
	int start, end, height;
	double where_hited;

	ray = 0;
	hit = 0;
	while (ray < game->res[X])
	{
		game->cameraX = 2 * ray / (double)(game->res[X]) - 1;
		game->raydir[X] = game->dir[X] + game->plane[X] * game->cameraX;
		game->raydir[Y] = game->dir[Y] + game->plane[Y] * game->cameraX;
		game->deltadist[X] = fabs(1 / game->raydir[X]);
		game->deltadist[Y] = fabs(1 / game->raydir[Y]);
		game->square[X] = (int)game->player[X];
		game->square[Y] = (int)game->player[Y];
		if (game->raydir[X] < 0)
		{
			game->step[X] = -1;
			game->sidedist[X] = (game->player[X] - game->square[X]) * game->deltadist[X];
		}
		else
		{
			game->step[X] = 1;
			game->sidedist[X] = (game->square[X] - game->player[X] + 1.0) * game->deltadist[X];
		}
		if (game->raydir[Y] < 0)
		{
			game->step[Y] = -1;
			game->sidedist[Y] = (game->player[Y] - game->square[Y]) * game->deltadist[Y];
		}
		else
		{
			game->step[Y] = 1;
			game->sidedist[Y] = (game->square[Y] - game->player[Y] + 1.0) * game->deltadist[Y];
		}
		while (!hit)
		{
			if (game->sidedist[X] < game->sidedist[Y])
			{
				game->sidedist[X] += game->deltadist[X];
				game->square[X] += game->step[X];
				side = 0;
			}
			else
			{
				game->sidedist[Y] += game->deltadist[Y];
				game->square[Y] += game->step[Y];
				side = 1;
			}
			if (game->map[game->square[X]][game->square[X]] == '1')
				hit = 1;
		}
		if (!side)
			game->perpwalldist = (game->square[X] - game->player[X] + (1 - game->step[X] / 2) / game->raydir[X]);
		else
			game->perpwalldist = (game->square[Y] - game->player[Y] + (1 - game->step[Y] / 2) / game->raydir[Y]);
		if (game->raydir[X] > 0)
		{
			if (game->raydir[Y] < 0)
			{
				if (!side)
					game->side = WE;
				else
					game->side = SO;
			}
			else
			{
				if (!side)
					game->side = WE;
				else
					game->side = NO;
			}
		}
		else
		{
			if (game->raydir[Y] < 0)
			{
				if (!side)
					game->side = EA;
				else
					game->side = SO;
			}
			else
			{
				if (!side)
					game->side = EA;
				else
					game->side = NO;
			}
		}
		height = (int)(game->res[Y] / game->perpwalldist);
		start = -height / 2 + game->res[Y] / 2;
		if (start < 0)
			start = 0;
		end = height / 2 + game->res[Y] / 2;
		if (end >= game->res[Y])
			end = game->res[Y] - 1;
		if (!side)
			where_hited = game->player[X] + game->perpwalldist * game->raydir[Y];
		else

		while (start < end)
		{

		}
	}
}

void	maze(t_game *game)
{
	if (game->event == W)
		step_up(game);
	else if (game->event == S)
		step_down(game);
	else if (game->event == A)
		step_left(game);
	else if (game->event == D)
		step_right(game);
	else if (game->event == ARRLEFT)
		turn_left(game);
	else if (game->event == ARRRIGHT)
		turn_right(game);
	get_img(game);
	fc_palette(game);
	raycasting(game);
}