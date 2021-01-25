#include "maze.h"

void lite_error(char *comment)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(comment, 1);
	exit(EXIT_FAILURE);
}

// void free_split(t_map **map)
// {
// 	while ((*map)->tokens--)
// 		free((*map)->split[(*map)->tokens]);
// 	free((*map)->split);
// }

void free_map(t_map **map)
{
	if ((*map)->line)
		free((*map)->line);
	if ((*map)->split)
		ft_twodarr_free((void ***)&(*map)->split, (*map)->tokens);
	if ((*map)->paths)
		ft_twodarr_free((void ***)&(*map)->paths, 5);
	if ((*map)->raw_map)
		free((*map)->raw_map);
	if ((*map)->map)
		ft_twodarr_free((void ***)&(*map)->map, ++(*map)->tokens);
	if ((*map)->fd != -1)
		close((*map)->fd);
	free(*map);
	*map = NULL;
}

void map_error(char *comment, t_map **map)
{
	free_map(map);
	lite_error(comment);
}

static void free_mlximg(t_game **game, int len)
{
	while (len--)
	{
		if ((*game)->ttrs[len])
		{
			if ((*game)->ttrs[len]->img)
				mlx_destroy_image((*game)->mlx, (*game)->ttrs[len]->img);
			free((*game)->ttrs[len]);
		}
	}
	free((*game)->ttrs);
	(*game)->ttrs = NULL;
}

void free_game(t_game **game)
{
	ft_twodarr_free((void ***)&(*game)->map, ++(*game)->rows);
	ft_twodarr_free((void ***)&(*game)->paths, 5);
	if ((*game)->ttrs)
		free_mlximg(game, 5);
	if ((*game)->win)
		mlx_destroy_window((*game)->mlx, (*game)->win);
	free(*game);
	*game = NULL;
}

void game_error(char *comment, t_game **game)
{
	free_game(game);
	lite_error(comment);
}