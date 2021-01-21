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

void map_error(char *comment, t_map **map)
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
	lite_error(comment);
}