#include "maze.h"

// cub3d map.cub --save

// + --save
static void	correct_args(int argc, char **argv, size_t filemap_len)
{
	if (filemap_len < 5 || ft_strendcmp(argv[1], ".cub", filemap_len - 4))
		lite_error(MAP_NAME_COMMENT);
}

static void correct_resolution(t_game *game)
{
	int sizex;
	int sizey;

	mlx_get_screen_size(game->mlx, &sizex, &sizey);
	if (game->res[X] > sizex)
		game->res[X] = sizex;
	if (game->res[Y] > sizey)
		game->res[Y] = sizey;
}

static void get_ttrimg(t_game *game, int flag)
{
	game->ttrs[flag] = (t_mlximg *)malloc(sizeof(t_mlximg));
	if (!game->ttrs[flag])
		game_error(MLX_MALLOC, &game);
	game->ttrs[flag]->img = mlx_xpm_file_to_image(game->mlx, game->paths[flag], &game->ttrs[flag]->xpm_width, \
							&game->ttrs[flag]->xpm_height);
	if (!game->ttrs[flag]->img)
		game_error(MLX_XPM, &game);
	game->ttrs[flag]->data = mlx_get_data_addr(game->ttrs[flag]->img, &game->ttrs[flag]->bits_in_texel, \
											&game->ttrs[flag]->bytes_line, &game->ttrs[flag]->little_endian);
}

static void prepare_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		game_error(MLX_INIT, &game);
	correct_resolution(game);
	game->win = mlx_new_window(game->mlx, game->res[X], game->res[Y], TITLE);
	if (!game->win)
		game_error(MLX_NEWWIN, &game);
	get_ttrimg(game, NO);
	get_ttrimg(game, EA);
	get_ttrimg(game, SO);
	get_ttrimg(game, WE);
	get_ttrimg(game, SPRITE);
}

static void event(int keycode, t_game *game)
{
	if (keycode == ESC)
		game_over(&game);
	else if (keycode == ARRLEFT || keycode == ARRRIGHT || \
		keycode == W || keycode == A || keycode == S || \
		keycode == D)
		game->event = keycode;
}

static void play(t_game *game)
{
	mlx_hook(game->win, 2, 0, &event, game); // перехват события
	//mlx_hook(game->win, 3, 1L<<1, &released, game);
	mlx_hook(game->win, 17, 0, &game_over, &game); // мышкой нажали на красный крестик
	mlx_loop_hook(game->mlx, &maze, game);
	mlx_loop(game->mlx);
}

int			main(int argc, char **argv)
{
	t_game *game;

	if (argc > 3 || argc < 2)
		lite_error(ARGS_NUM_COMMENT);
	correct_args(argc, argv, ft_strlen(argv[1]));
	game = parser(argv[1]);
	prepare_mlx(game);
	play(game);
	
	return (0);
}



//t_mlx_manager *mlx;

	//mlx->ptr = mlx_init();
	//mlx->window = mlx_new_window(mlx->ptr, mlx->img_w, mlx->img_h, "cub3d");