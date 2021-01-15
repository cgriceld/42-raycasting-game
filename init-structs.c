#include "maze.h"

int	init_map(t_map **map, const char *map_file)
{
	*map = (t_map *)malloc(sizeof(t_map));
	if (!*map)
		return (lite_error(MALLOC_TMAP_INIT));
	(*map)->fd = open(map_file, O_RDONLY);
	if ((*map)->fd == -1)
		return (map_error(NEG_FD, map));
}
