#include "maze.h"

/*
** [planeX dirX] * [cosX  -sinX]
** [planeY dirY] * [sinX   cosX]
** > [planeX * cosX - planeY * sinX   dirX * cosX - dirY * sinX]
** > [planeX * sinX + planeY * cosX   dirX * sinX + dirY * cosX]
*/

void	turn_right(t_game *game)
{
	double planeprev[X];
	double dirprev[X];

	planeprev[X] = game->plane[X];
	dirprev[X] = game->dir[X];
	game->plane[X] = game->plane[X] * cos(0.09) - game->plane[Y] * sin(0.09);
	game->plane[Y] = planeprev[X] * sin(0.09) + game->plane[Y] * cos(0.09);
	game->dir[X] = game->dir[X] * cos(0.09) - game->dir[Y] * sin(0.09);
	game->dir[Y] = dirprev[X] * sin(0.09) + game->dir[Y] * cos(0.09);
}

void	turn_left(t_game *game)
{
	double planeprev[X];
	double dirprev[X];

	planeprev[X] = game->plane[X];
	dirprev[X] = game->dir[X];
	game->plane[X] = game->plane[X] * cos(-0.09) - game->plane[Y] * sin(-0.09);
	game->plane[Y] = planeprev[X] * sin(-0.09) + game->plane[Y] * cos(-0.09);
	game->dir[X] = game->dir[X] * cos(-0.09) - game->dir[Y] * sin(-0.09);
	game->dir[Y] = dirprev[X] * sin(-0.09) + game->dir[Y] * cos(-0.09);
}
