/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:07:43 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/15 19:21:46 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

static void		boarders_wall(t_game *game)
{
	game->wallheight = (int)(game->res[Y] / game->dist);
	game->wallstart = game->res[Y] / 2 - game->wallheight / 2;
	game->wallend = game->res[Y] / 2 + game->wallheight / 2;
	game->wallstart = game->wallstart < 0 ? 0 : game->wallstart;
	game->wallend = game->wallend >= game->res[Y] ? \
					game->res[Y] - 1 : game->wallend;
}

static void		draw_slice(t_mlximg *wall, t_game *game, int ray)
{
	int		hit_ttrx;
	double	where_hit;
	double	step;
	double	hit_ttry;

	boarders_wall(game);
	where_hit = !game->currside ? game->player[Y] + game->dist \
	* game->ray[Y] : game->player[X] + game->dist * game->ray[X];
	where_hit -= floor(where_hit);
	hit_ttrx = (int)(where_hit * (double)(wall->img_width));
	if ((!game->currside && game->ray[X] > 0) || \
		(game->currside && game->ray[Y] < 0))
		hit_ttrx = wall->img_width - hit_ttrx - 1;
	step = 1.0 * wall->img_height / game->wallheight;
	while (game->wallstart < game->wallend)
	{
		hit_ttry = (256 * game->wallstart - 128 * game->res[Y] + \
					128 * game->wallheight) * step / 256;
		game->maze->data[game->maze->img_width * game->wallstart + ray] = \
		wall->data[wall->img_width * (int)hit_ttry + hit_ttrx];
		game->wallstart++;
	}
}

static t_mlximg	*get_slice(t_game *game, int ray)
{
	t_mlximg *wall;

	if (game->ray[X] > 0 && game->ray[Y] >= 0)
		wall = !game->currside ? game->ttrs[EA] : game->ttrs[SO];
	if (game->ray[X] > 0 && game->ray[Y] < 0)
		wall = !game->currside ? game->ttrs[EA] : game->ttrs[NO];
	if (game->ray[X] <= 0 && game->ray[Y] < 0)
		wall = !game->currside ? game->ttrs[WE] : game->ttrs[NO];
	if (game->ray[X] <= 0 && game->ray[Y] >= 0)
		wall = !game->currside ? game->ttrs[WE] : game->ttrs[SO];
	game->dist = !game->currside ? \
	(game->square[X] - game->player[X] + (1 - game->dirmove[X]) / 2) / \
	game->ray[X] : \
	(game->square[Y] - game->player[Y] + (1 - game->dirmove[Y]) / 2) / \
	game->ray[Y];
	game->depth[ray] = game->dist;
	return (wall);
}

static void		find_wall(t_game *game)
{
	int	wall;

	wall = 0;
	while (!wall)
	{
		if (game->path[Y] < game->path[X])
		{
			game->path[Y] += game->next[Y];
			game->square[Y] += game->dirmove[Y];
			game->currside = 1;
		}
		else if (game->path[X] < game->path[Y])
		{
			game->path[X] += game->next[X];
			game->square[X] += game->dirmove[X];
			game->currside = 0;
		}
		if (game->map[game->square[Y]][game->square[X]] == '1')
			wall++;
	}
}

void			throw_rays(t_game *game)
{
	int		ray;
	double	plane_point;

	ray = 0;
	while (ray < game->res[X])
	{
		game->square[X] = (int)game->player[X];
		game->square[Y] = (int)game->player[Y];
		plane_point = 2 * ray / (double)(game->res[X]) - 1;
		game->ray[X] = game->dir[X] + game->plane[X] * plane_point;
		game->ray[Y] = game->dir[Y] + game->plane[Y] * plane_point;
		game->next[X] = fabs(1 / game->ray[X]);
		game->next[Y] = fabs(1 / game->ray[Y]);
		game->dirmove[X] = game->ray[X] > 0 ? 1 : -1;
		game->path[X] = game->ray[X] > 0 ? \
		(1.0 - (game->player[X] - game->square[X])) * game->next[X] : \
		(game->player[X] - game->square[X]) * game->next[X];
		game->dirmove[Y] = game->ray[Y] > 0 ? 1 : -1;
		game->path[Y] = game->ray[Y] > 0 ? \
		(1.0 - (game->player[Y] - game->square[Y])) * game->next[Y] : \
		(game->player[Y] - game->square[Y]) * game->next[Y];
		find_wall(game);
		draw_slice(get_slice(game, ray), game, ray);
		ray++;
	}
}
