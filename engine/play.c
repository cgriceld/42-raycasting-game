#include "maze.h"

int			klick(int key, t_game *game)
{
	if (key == 0x35)
		game_over(&game);
	else if (key == 0x0D)
		game->event |= W;
	else if (!key)
		game->event |= A;
	else if (key == 0x01)
		game->event |= S;
	else if (key == 0x02)
		game->event |= D;
	else if (key == 0x7B)
		game->event |= LEFT;
	else if (key == 0x7C)
		game->event |= RIGHT;
	return (TRUE);
}

int			unclick(int key, t_game *game)
{
	if (key == 0x0D || !key || key == 0x01 || key == 0x02 \
		|| key == 0x7B || key == 0x7C)
		game->event &= EMPTY;
	return (TRUE);
}

static void	get_canvas(t_game *game)
{
	unsigned int *pxl;

	game->maze = (t_mlximg *)malloc(sizeof(t_mlximg));
	if (!game->maze)
		game_error(MLX_MALLOC, &game);
	game->maze->img_width = game->res[X];
	game->maze->img_height = game->res[Y];
	game->maze->img = mlx_new_image(game->mlx, game->res[X], game->res[Y]);
	if (!game->maze->img)
		game_error(MLX_NEWIMG, &game);
	game->maze->data = \
	(unsigned int *)mlx_get_data_addr(game->maze->img, \
	&game->maze->bits_in_texel, &game->maze->bytes_line, \
	&game->maze->little_endian);
	pxl = game->maze->data;
	while (pxl < game->maze->data + game->res[Y] / 2 * game->res[X])
		*pxl++ = game->colors[CEILING];
	while (pxl < game->maze->data + game->res[Y] * game->res[X])
		*pxl++ = game->colors[FLOOR];
}

int			play(t_game *game)
{
	if (game->event & EMPTY)
		return (TRUE);
	get_canvas(game);
	if (game->event & W)
		step_up(game);
	else if (game->event & A)
		step_left(game);
	else if (game->event & S)
		step_down(game);
	else if (game->event & D)
		step_right(game);
	else if (game->event & LEFT)
		turn_left(game);
	else if (game->event & RIGHT)
		turn_right(game);
	throw_rays(game);
	sort_sprites(game);
	sprites(game);
	game->save & SAVE ? save(game) : \
	mlx_put_image_to_window(game->mlx, game->win, game->maze->img, 0, 0);
	mlx_destroy_image(game->mlx, game->maze->img);
	ft_ptr_free((void **)&game->maze);
	if (game->save & SAVE)
		game_over(&game);
	return (TRUE);
}
