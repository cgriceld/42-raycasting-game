#include "maze.h"

int lite_error(const char *comment)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(comment, 1);
	return (false);
}

int map_error(const char *comment, t_map *map)
{
	// free map malloced contents
	free(map);
	return (lite_error(comment));
}