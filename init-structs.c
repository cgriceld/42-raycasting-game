#include "maze.h"

void	init_map(t_map **map, const char *map_file)
{
	*map = (t_map *)malloc(sizeof(t_map));
	if (!*map)
		lite_error(MALLOC_PARSE);
	(*map)->line = NULL;
	(*map)->split = NULL;
	(*map)->paths = (char **)malloc(sizeof(char *) * 5);
	if (!(*map)->paths)
		map_error(MALLOC_PARSE, map);
	(*map)->paths[NO] = NULL;
	(*map)->paths[EA] = NULL;
	(*map)->paths[SO] = NULL;
	(*map)->paths[WE] = NULL;
	(*map)->paths[SPRITE] = NULL;
	(*map)->fd = open(map_file, O_RDONLY);
	if ((*map)->fd == -1)
		map_error(NEG_FD, map);
	(*map)->colors[GET_ALL] = 0;
	(*map)->colors[FLOOR] = 0;
	(*map)->colors[CEILING] = 0;
	(*map)->res_x = 0;
	(*map)->res_y = 0;
	(*map)->raw_map = NULL;
	(*map)->map_done = 0;
}
