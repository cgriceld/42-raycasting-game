/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:58:12 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/17 13:43:28 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

/*
** Moves if no wall or sprite on the way
*/

static void	check_move(t_game *game, int flag, double new)
{
	if (flag == X && game->map[(int)(game->player[Y])][(int)(new)] != '1' && \
		game->map[(int)(game->player[Y])][(int)(new)] != '4')
		game->player[X] = new;
	if (flag == Y && game->map[(int)(new)][(int)(game->player[X])] != '1' && \
		game->map[(int)(new)][(int)(game->player[X])] != '4')
		game->player[Y] = new;
}

void		step_up(t_game *game)
{
	double move;

	move = game->player[X] + 0.03 * game->dir[X];
	check_move(game, X, move);
	move = game->player[Y] + 0.03 * game->dir[Y];
	check_move(game, Y, move);
}

void		step_left(t_game *game)
{
	double move;

	move = game->player[X] - 0.03 * game->plane[X];
	check_move(game, X, move);
	move = game->player[Y] - 0.03 * game->plane[Y];
	check_move(game, Y, move);
}

void		step_down(t_game *game)
{
	double move;

	move = game->player[X] - 0.03 * game->dir[X];
	check_move(game, X, move);
	move = game->player[Y] - 0.03 * game->dir[Y];
	check_move(game, Y, move);
}

void		step_right(t_game *game)
{
	double move;

	move = game->player[X] + 0.03 * game->plane[X];
	check_move(game, X, move);
	move = game->player[Y] + 0.03 * game->plane[Y];
	check_move(game, Y, move);
}
