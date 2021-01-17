#include "maze.h"

int		ft_strdigits(char *str)
{
	while (*str && ft_isdigit(*str))
		str++;
	return (!*str ? 1 : 0);
}

static int parse_resolution(t_map *map)
{
	
	if (!(ft_strdigits(map->split[1])) || !(ft_strdigits(map->split[2])) || \
		(map->res_x = ft_atoi(map->split[1])) <= 0|| \
		(map->res_y = ft_atoi(map->split[2])) <= 0)
		return (map_error(RES_ERR, &map));
	if (map->res_x > DEFAULT_RES_X)
		map->res_x = DEFAULT_RES_X;
	if (map->res_y > DEFAULT_RES_Y)
		map->res_y = DEFAULT_RES_Y;
	return (true);
}

static int process_line(t_map *map)
{
	size_t first;

	map->split = ft_split(map->line, ' ');
	if (!map->split)
		return (map_error(MALLOC_TMAP_INIT, &map));
	map->tokens = twodarr_len((void **)map->split);
	if (!map->tokens) // empty string, [[NULL]]
	{
		free(map->split);
		return (true); // continue reading
	}
	first = ft_strlen(map->split[0]); // len of first param
	if (first == 1 && !ft_strncmp(map->split[0], "R", 1) && map->tokens == 3)
		return (parse_resolution(map));
	return (map_error(UNKNOWN_CH, &map));
}

void	parser(const char *map_file)
{
	t_map *map;
	int res;

	if (!init_map(&map, map_file))
		return ;
	while ((res = get_next_line(map->fd, &(map->line))) >= 0)
	{
		if (!process_line(map))
			break ;
		free(map->line);
	}
}
