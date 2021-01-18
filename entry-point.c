#include "maze.h"

// cub3d map.cub --save

// + --save
static void	correct_args(int argc, char **argv, size_t filemap_len)
{
	if (filemap_len < 5 || ft_strendcmp(argv[1], ".cub", filemap_len - 4))
		lite_error(MAP_NAME_COMMENT);
}

int			main(int argc, char **argv)
{
	if (argc > 3 || argc < 2)
		lite_error(ARGS_NUM_COMMENT);
	correct_args(argc, argv, ft_strlen(argv[1]));
	parser(argv[1]);
	return (0);
}



//t_mlx_manager *mlx;

	//mlx->ptr = mlx_init();
	//mlx->window = mlx_new_window(mlx->ptr, mlx->img_w, mlx->img_h, "cub3d");