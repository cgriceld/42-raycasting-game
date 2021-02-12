#include "maze.h"

/*
** Moves if no wall or sprite on the way
*/

static void	check_move(t_game *game, int flag, double new)
{
	if (flag == X && game->map[(int)(game->pos[Y])][(int)(new)] != '1' && \
		game->map[(int)(game->pos[Y])][(int)(new)] != '4')
		game->pos[X] = new;
	if (flag == Y && game->map[(int)(new)][(int)(game->pos[X])] != '1' && \
		game->map[(int)(new)][(int)(game->pos[X])] != '4')
		game->pos[Y] = new;
}

void		step_up(t_game *game)
{
	double move;

	move = game->pos[X] + 0.03 * game->dir[X];
	check_move(game, X, move);
	move = game->pos[Y] + 0.03 * game->dir[Y];
	check_move(game, Y, move);
}

void		step_left(t_game *game)
{
	double move;

	move = game->pos[X] - 0.03 * game->plane[X];
	check_move(game, X, move);
	move = game->pos[Y] - 0.03 * game->plane[Y];
	check_move(game, Y, move);
}

void		step_down(t_game *game)
{
	double move;

	move = game->pos[X] - 0.03 * game->dir[X];
	check_move(game, X, move);
	move = game->pos[Y] - 0.03 * game->dir[Y];
	check_move(game, Y, move);
}

void		step_right(t_game *game)
{
	double move;

	move = game->pos[X] + 0.03 * game->plane[X];
	check_move(game, X, move);
	move = game->pos[Y] + 0.03 * game->plane[Y];
	check_move(game, Y, move);
}