#include "maze.h"
#include <stdio.h>

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

static void parse_ttr(t_map *map, int side)
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

static int get_rgb(int red, int green, int blue)
{
	return ((red <= 255 && green <= 255 && blue <= 255) ? \
	(red << 16 | green << 8 | blue) : -1);
}

static void parse_color(t_map *map, int side)
{
	char **colors;
	size_t tokens;

	if (map->colors[side])
		map_error(COLOR_DOUBLE, &map);
	colors = ft_split(map->split[1], ',');
	if (!colors)
		map_error(MALLOC_PARSE, &map);
	tokens = twodarr_len((void **)colors);
	if (tokens != 3 || !(ft_strdigits(colors[0])) || \
		!(ft_strdigits(colors[1])) || !(ft_strdigits(colors[2])))
	{
		twodarr_free((void **)colors, tokens);
		map_error(COLOR_ERR, &map);
	}
	map->colors[side] = get_rgb(ft_atoi(colors[0]), ft_atoi(colors[1]), \
								ft_atoi(colors[2]));
	twodarr_free((void **)colors, tokens);
	if (map->colors[side] < 0)
		map_error(COLOR_0255, &map);
	map->colors[GET_ALL]++;

	// printf("transparent : %d\n", (map->colors[side] & (0xFF << 24)));
	// printf("red : %d\n", (map->colors[side] & (0xFF << 16)));
	// printf("green : %d\n", (map->colors[side] & (0xFF << 8)));
	// printf("blue : %d\n", (map->colors[side] & 0xFF));
}

static void process_line(t_map *map, size_t first)
{
	if (first == 1 && map->tokens == 3 && map->split[0][0] == 'R')
		parse_resolution(map);
	else if (first == 1 && map->tokens == 2)
	{
		if (map->split[0][0] == 'S')
			parse_ttr(map, SPRITE);
		else if (map->split[0][0] == 'F')
			parse_color(map, FLOOR);
		else if (map->split[0][0] == 'C')
			parse_color(map, CEILING);
	}
	else if (first == 2 && map->tokens == 2)
	{
		if (!ft_strncmp(map->split[0], "NO", 2))
			parse_ttr(map, NO);
		else if (!ft_strncmp(map->split[0], "EA", 2))
			parse_ttr(map, EA);
		else if (!ft_strncmp(map->split[0], "SO", 2))
			parse_ttr(map, SO);
		else if (!ft_strncmp(map->split[0], "WE", 2))
			parse_ttr(map, WE);
	}
	else
		map_error(UNKNOWN_CH, &map);
}

static int map_ready(t_map *map)
{
	return (map->res_x && map->res_y && map->paths[NO] && map->paths[EA] && \
			map->paths[SO] && map->paths[WE] && map->paths[SPRITE] && \
			map->colors[GET_ALL] == 2);
}

static void get_raw_map(t_map *map)
{
	char *tmp_line;
	char *tmp_map;

	if (map->reading < 0)
		map_error(GNL_ERROR, &map);
	if (!*map->line)
		map_error(MAP_EMPTY_LINE, &map);
	if (!ft_strchset(map->line, MAP_SET))
		map_error(UNKNOWN_CH_MAP, &map);
	tmp_line = ft_strjoin(map->line, "\n");
	if (!tmp_line)
		map_error(MALLOC_PARSE, &map);
	tmp_map = map->raw_map;
	map->raw_map = ft_strjoin(map->raw_map, tmp_line);
	free(tmp_map);
	free(tmp_line);
	if (!map->raw_map)
		map_error(MALLOC_PARSE, &map);
	free(map->line);
	map->line = NULL;
}

static void process_map(t_map *map)
{
	if (!ft_strchset(map->line, MAP_SET))
		map_error(UNKNOWN_CH_MAP, &map);
	map->raw_map = ft_strjoin(map->line , "\n");
	if (!map->raw_map)
		map_error(MALLOC_PARSE, &map);
	free(map->line);
	map->line = NULL;
	while ((map->reading = get_next_line(map->fd, &(map->line))))
		get_raw_map(map);
	get_raw_map(map);
	map->map_done++;
}

static void	process_parsing(t_map *map)
{
	size_t first;

	map->split = ft_split(map->line, ' ');
	if (!map->split)
		map_error(MALLOC_PARSE, &map);
	map->tokens = twodarr_len((void **)map->split);
	first = ft_strlen(map->split[0]); // len of first param
	process_line(map, first);
	twodarr_free((void **)map->split, map->tokens);
	map->split = NULL;
	free(map->line);
	map->line = NULL;
}

void	parser(const char *map_file)
{
	t_map	*map;

	init_map(&map, map_file);
	while ((map->reading = get_next_line(map->fd, &(map->line))))
	{
		if (map->reading < 0)
			map_error(GNL_ERROR, &map);
		if (!(*map->line)) // empty line
			continue ;
		map_ready(map) ? process_map(map) : process_parsing(map);
	}
	if (!map->reading && !map->map_done)
		map_error(NO_MAP, &map);
}
