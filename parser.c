#include "maze.h"

static void parse_resolution(t_map *map)
{
	if (map->res_x)
		map_error(RES_DOUBLE, &map);
	if (!(ft_strdigits(map->split[1])) || !(ft_strdigits(map->split[2])))
		map_error(RES_ERR, &map);
	map->res_x = ft_atoi(map->split[1]);
	map->res_y = ft_atoi(map->split[2]);
	if (!map->res_x || !map->res_y)
		map_error(RES_ERR, &map);
	map->res_x = map->res_x > DEFAULT_RES_X ? DEFAULT_RES_X : map->res_x;
	map->res_y = map->res_y > DEFAULT_RES_Y ? DEFAULT_RES_Y : map->res_y;
}

static void parse_map(t_map *map, int side)
{
	int test_fd;

	if (map->paths[side])
		map_error(PATH_DOUBLE, &map);
	test_fd = open(map->split[1], O_RDONLY);
	test_fd != -1 ? close(test_fd) : map_error(INVALID_PATH, &map);
	map->paths[side] = ft_strdup(map->split[1]);
	if (!map->paths[side])
		map_error(MALLOC_PARSE, &map);
}

static void process_line(t_map *map)
{
	size_t first;

	map->split = ft_split(map->line, ' ');
	if (!map->split)
		map_error(MALLOC_PARSE, &map);
	map->tokens = twodarr_len((void **)map->split);
	if (!map->tokens) // empty string, [[NULL]]
		return ; // continue reading
	first = ft_strlen(map->split[0]); // len of first param
	if (first == 1 && map->tokens == 3 && map->split[0][0] == 'R')
		parse_resolution(map);
	if (first == 1 && map->tokens == 2 && map->split[0][0] == 'S')
		parse_map(map, SPRITE);
	else if (first == 2 && map->tokens == 2)
	{
		if (!ft_strncmp(map->split[0], "NO", 2))
			parse_map(map, NO);
		else if (!ft_strncmp(map->split[0], "EA", 2))
			parse_map(map, EA);
		else if (!ft_strncmp(map->split[0], "SO", 2))
			parse_map(map, SO);
		else if (!ft_strncmp(map->split[0], "WE", 2))
			parse_map(map, WE);
	}
	else
		map_error(UNKNOWN_CH, &map);
}

void	process_parsing(t_map **map)
{
	process_line(*map);
	twodarr_free((void **)(*map)->split, (*map)->tokens);
	free((*map)->line);
}

void	parser(const char *map_file)
{
	t_map	*map;
	int		reading;

	init_map(&map, map_file);
	while ((reading = get_next_line(map->fd, &(map->line))))
	{
		if (reading < 0)
			map_error(GNL_ERROR, &map);
		process_parsing(&map);
	}
	process_parsing(&map);
}
