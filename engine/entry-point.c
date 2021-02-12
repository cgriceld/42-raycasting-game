#include "maze.h"

static void	correct_args(int argc, char **argv, size_t filemap_len, \
						unsigned char *save)
{
	if (filemap_len < 5 || ft_strendcmp(argv[1], ".cub", filemap_len - 4))
		lite_error(MAP_NAME_COMMENT);
	if (argc == 3)
		!ft_strncmp(argv[2], "--save", 6) ? (*save |= SAVE) : lite_error(SAVE_ERR);
	if (*save & SAVE)
		write(1, "SAVING...\n", 10);
}

static void	get_ttrs(t_game *game, int flag)
{
	game->ttrs[flag] = (t_mlximg *)malloc(sizeof(t_mlximg));
	if (!game->ttrs[flag])
		game_error(MLX_MALLOC, &game);
	game->ttrs[flag]->img_width = 0;
	game->ttrs[flag]->img_height = 0;
	game->ttrs[flag]->img = \
	mlx_xpm_file_to_image(game->mlx, game->paths[flag], \
				&game->ttrs[flag]->img_width, &game->ttrs[flag]->img_height);
	if (!game->ttrs[flag]->img)
		game_error(MLX_XPM, &game);
	game->ttrs[flag]->data = \
	(unsigned int *)mlx_get_data_addr(game->ttrs[flag]->img, \
	&game->ttrs[flag]->bits_in_texel, &game->ttrs[flag]->bytes_line, \
	&game->ttrs[flag]->little_endian);
}

static void	prepare_mlx(t_game *game)
{
	int sizex;
	int sizey;

	game->mlx = mlx_init();
	if (!game->mlx)
		game_error(MLX_INIT, &game);
	mlx_get_screen_size(game->mlx, &sizex, &sizey);
	game->res[X] = game->res[X] > sizex ? sizex : game->res[X];
	game->res[Y] = game->res[Y] > sizey ? sizey : game->res[Y];
	if (!(game->save & SAVE))
	{
		game->win = \
			mlx_new_window(game->mlx, game->res[X], game->res[Y], TITLE);
		if (!game->win)
			game_error(MLX_NEWWIN, &game);
	}
	get_ttrs(game, NO);
	get_ttrs(game, EA);
	get_ttrs(game, SO);
	get_ttrs(game, WE);
	get_ttrs(game, SPRITE);
}

int			main(int argc, char **argv)
{
	t_game			*game;
	unsigned char	save;

	if (argc > 3 || argc < 2)
		lite_error(ARGS_NUM_COMMENT);
	save = EMPTY;
	correct_args(argc, argv, ft_strlen(argv[1]), &save);
	parser(argv[1], &game);
	game->save = save;
	prepare_mlx(game);
	if (game->save & SAVE)
		play(game);
	mlx_hook(game->win, 17, 0, &game_over, &game);
	mlx_hook(game->win, 2, 0, &klick, game);
	mlx_hook(game->win, 3, 0, &unclick, game);
	mlx_loop_hook(game->mlx, &play, game);
	mlx_loop(game->mlx);
	return (TRUE);
}

