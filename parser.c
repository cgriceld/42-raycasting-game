#include "maze.h"

void	parser(const char *map_file)
{
	t_map *map;

	if (!init_map(&map, map_file))
		return ;
	while (get_next_line())
}