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

static void get_mlximg(t_game *game)
{
	
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
}

int			main(int argc, char **argv)
{
	t_game *game;

	if (argc > 3 || argc < 2)
		lite_error(ARGS_NUM_COMMENT);
	correct_args(argc, argv, ft_strlen(argv[1]));
	game = parser(argv[1]);
	prepare_mlx(game);
	
	return (0);
}



//t_mlx_manager *mlx;

	//mlx->ptr = mlx_init();
	//mlx->window = mlx_new_window(mlx->ptr, mlx->img_w, mlx->img_h, "cub3d");