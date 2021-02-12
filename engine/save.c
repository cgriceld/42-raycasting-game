#include "maze.h"

/*
** File header:
** BM (2)
** whole size in bytes (4)
** reserved (2 * 2)
** offset, starting adress (4)
**
** Information header:
** header size in bytes (4)
** width in pixels (4)
** height in pixels (4)
** number of color planes (2)
** bits per pixel (2)
** 
*/

static void header_info(t_game *game, int fd, int *param, int *padding)
{
	if (write(fd, "BM", 2) < 0)
		game_error(WRITE_ERR, &game);
	*padding = 4 - ((3 * game->res[X]) % 4);
	*param = 14 + 40 + (3 * game->res[X] + *padding) * game->res[Y];
	if (write(fd, param, 4) < 0)
		game_error(WRITE_ERR, &game);
	*param = 0;
	if (write(fd, param, 4) < 0)
		game_error(WRITE_ERR, &game);
	*param = 54;
	if (write(fd, param, 4) < 0)
		game_error(WRITE_ERR, &game);
	*param = 40;
	if (write(fd, param, 4) < 0 || write(fd, &game->res[X], 4) < 0 || \
		write(fd, &game->res[Y], 4) < 0)
		game_error(WRITE_ERR, &game);
	*param = 1;
	if (write(fd, param, 2) < 0)
		game_error(WRITE_ERR, &game);
	*param = 32;
	if (write(fd, param, 2) < 0)
		game_error(WRITE_ERR, &game);
	*param = 0;
	if (write(fd, param, 24) < 0)
		game_error(WRITE_ERR, &game);
}

void		save(t_game *game)
{
	int fd;
	int row;
	int column;
	int	param;
	int padding;

	fd = open("cub3D.bmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		game_error(FD_ERR, &game);
	header_info(game, fd, &param, &padding);
	column = game->res[Y];
	while (--column >= 0)
	{
		row = 0;
		while (row < game->res[X])
		{
			if (write(fd, \
				&(game->maze->data[(game->res[X]) * column + row++]), 4) < 0)
				game_error(WRITE_ERR, &game);
		}
	}
	close(fd);
}
