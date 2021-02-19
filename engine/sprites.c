/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:51:13 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/19 17:07:38 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

static void	boarders_sprite(t_game *game, int *start, int *end)
{
	start[Y] = game->res[Y] / 2 - game->spr->height / 2;
	end[Y] = game->res[Y] / 2 + game->spr->height / 2;
	start[X] = game->spr->wherex - game->spr->width / 2;
	end[X] = game->spr->wherex + game->spr->width / 2;
	start[Y] = start[Y] < 0 ? 0 : start[Y];
	end[Y] = end[Y] >= game->res[Y] ? game->res[Y] - 1 : end[Y];
	start[X] = start[X] < 0 ? 0 : start[X];
	end[X] = end[X] >= game->res[X] ? game->res[X] - 1 : end[X];
}

static void	y_loop(t_game *game, int pxly, int currw, int x)
{
	double			steph;
	double			currh;
	unsigned int	pxl;

	steph = 1.0 * game->ttrs[SPRITE]->img_height / game->spr->height;
	currh = (256 * pxly - 128 * game->res[Y] + 128 * game->spr->height) \
														* steph / 256;
	pxl = game->ttrs[SPRITE]->data[game->ttrs[SPRITE]->img_width * \
									(int)currh + currw];
	if (pxl & NO_TRANSPARENT)
		game->maze->data[game->maze->img_width * pxly + x] = pxl;
}

static void	draw_item(t_game *game, double proj)
{
	int		start[2];
	int		end[2];
	int		pxly;
	double	stepw;
	double	currw;

	boarders_sprite(game, start, end);
	stepw = 1.0 * game->ttrs[SPRITE]->img_width / game->spr->width;
	while (start[X] < end[X])
	{
		currw = (256 * start[X] + 128 * game->spr->width - \
				256 * game->spr->wherex) * stepw / 256;
		if (start[X] > 0 && start[X] < game->res[X] && \
			proj < game->depth[start[X]])
		{
			pxly = start[Y];
			while (pxly < end[Y])
			{
				y_loop(game, pxly, (int)currw, start[X]);
				pxly++;
			}
		}
		start[X]++;
	}
}

/*
** [dirY      -dirX] *  ______________1_____________   * [spriteX]
** [-planeY  planeX] *  planeX * dirY - dirX * planeY  * [spriteY]
*/

void		sprites(t_game *game)
{
	int		tmp;
	double	curr[2];
	double	proj[2];
	double	mult;

	tmp = 0;
	mult = 1.0 / (game->plane[X] * game->dir[Y] - \
					game->dir[X] * game->plane[Y]);
	while (tmp < game->numspr)
	{
		curr[X] = game->sprites[tmp][X] - game->player[X];
		curr[Y] = game->sprites[tmp][Y] - game->player[Y];
		proj[X] = mult * (game->dir[Y] * curr[X] - game->dir[X] * curr[Y]);
		proj[Y] = mult * (game->plane[X] * curr[Y] - game->plane[Y] * curr[X]);
		if (proj[Y] < 0)
		{
			tmp++;
			continue;
		}
		game->spr->width = (int)(game->res[X] / proj[Y]);
		game->spr->height = (int)(game->res[Y] / proj[Y]);
		game->spr->wherex = (int)((game->res[X] / 2) * (1 + proj[X] / proj[Y]));
		draw_item(game, proj[Y]);
		tmp++;
	}
}
