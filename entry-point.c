#include "maze.h"

// cub3d map.cub --save

static int	correct_args(int argc, char **argv, size_t filemap_len)
{
	if (argc > 3 || argc < 2)
		args_error_manager(ARGS_NUM, ARGS_NUM_COMMENT);
	else if (filemap_len < 5 || ft_strendcmp(argv[1], ".cub", filemap_len - 4))
		args_error_manager(MAP_NAME, MAP_NAME_COMMENT);
}

int	main(int argc, char **argv)
{
	correct_args(argc, argv, ft_strlen(argv[1]));
	return (0);
}

//t_mlx_manager *mlx;

	//mlx->ptr = mlx_init();
	//mlx->window = mlx_new_window(mlx->ptr, mlx->img_w, mlx->img_h, "cub3d");