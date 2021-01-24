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

void free_game(t_game **game)
{
	ft_twodarr_free((void ***)&(*game)->map, ++(*game)->rows);
	ft_twodarr_free((void ***)&(*game)->paths, 5);
	free(*game);
	*game = NULL;
}

void game_error(char *comment, t_game **game)
{
	free_game(game);
	lite_error(comment);
}