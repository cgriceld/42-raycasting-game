#include "maze.h"

int lite_error(char *comment)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(comment, 1);
	return (false);
}

int map_error(char *comment, t_map **map)
{
	// free map malloced contents
	if ((*map)->line)
		free((*map)->line);
	if ((*map)->split)
	{
		while ((*map)->tokens--)
			free((*map)->split[(*map)->tokens]);
		free((*map)->split);
	}
	if ((*map)->fd != -1)
		close((*map)->fd);
	free(*map);
	return (lite_error(comment));
}