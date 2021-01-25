#include "maze.h"
#include <stdio.h>

static void parse_resolution(t_map *map)
{
	if (map->res[X])
		map_error(RES_DOUBLE, &map);
	if (!(ft_strdigits(map->split[1])) || !(ft_strdigits(map->split[2])))
		map_error(RES_ERR, &map);
	map->res[X] = ft_atoi(map->split[1]);
	map->res[Y] = ft_atoi(map->split[2]);
	if (!map->res[X] || !map->res[Y])
		map_error(RES_ERR, &map);
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

	if ((side == FLOOR && map->colors[GET_FLOOR]) || \
		(side == CEILING && map->colors[GET_CEILING]))
		map_error(COLOR_DOUBLE, &map);
	colors = ft_split(map->split[1], ',');
	if (!colors)
		map_error(MALLOC_PARSE, &map);
	tokens = ft_twodarr_len((void **)colors);
	if (tokens != 3 || !(ft_strdigits(colors[0])) || \
		!(ft_strdigits(colors[1])) || !(ft_strdigits(colors[2])))
	{
		ft_twodarr_free((void ***)&colors, tokens);
		map_error(COLOR_ERR, &map);
	}
	map->colors[side] = get_rgb(ft_atoi(colors[0]), ft_atoi(colors[1]), \
								ft_atoi(colors[2]));
	ft_twodarr_free((void ***)&colors, tokens);
	if (map->colors[side] < 0)
		map_error(COLOR_0255, &map);
	side == FLOOR ? map->colors[GET_FLOOR]++ : map->colors[GET_CEILING]++;

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
	return (map->res[X] && map->paths[NO] && map->paths[EA] && \
			map->paths[SO] && map->paths[WE] && map->paths[SPRITE] && \
			map->colors[GET_FLOOR] && map->colors[GET_CEILING]);
}

static void find_player(t_map *map)
{
	char *player;

	if ((player = ft_strchrset(map->line, PLAYER_SET)))
	{
		if (map->player[GET_ALL])
			map_error(TWO_PLAYERS, &map);
		map->player[X] = map->tokens + 0.5;
		map->player[Y] = player - map->line + 0.5;
		if (*player == 'N')
		{
			map->dir[X] = 0;
			map->dir[Y] = -1;
			map->plane[X] = 0.66;
			map->plane[Y] = 0;
		}
		else if (*player == 'E')
		{
			map->dir[X] = 1;
			map->dir[Y] = 0;
			map->plane[X] = 0;
			map->plane[Y] = 0.66;
		}
		else if (*player == 'S')
		{
			map->dir[X] = 0;
			map->dir[Y] = 1;
			map->plane[X] = -0.66;
			map->plane[Y] = 0;
		}
		else
		{
			map->dir[X] = -1;
			map->dir[Y] = 0;
			map->plane[X] = 0;
			map->plane[Y] = -0.66;
		}
		map->player[GET_ALL]++;
	}
}

static void find_sprite(t_map *map)
{
	// if (ft_strchr(map->line, '2'))
	// {

	// }
}

static void get_raw_map(t_map *map, int reading)
{
	char *tmp_line;
	char *tmp_map;

	if (reading < 0)
		map_error(GNL_ERROR, &map);
	if (!*map->line)
		map_error(MAP_EMPTY_LINE, &map);
	if (!ft_strinset(map->line, MAP_SET))
		map_error(UNKNOWN_CH_MAP, &map);
	map->tokens++;
	find_player(map);
	find_sprite(map);
	tmp_line = ft_strjoin(map->line, "\n");
	if (!tmp_line)
		map_error(MALLOC_PARSE, &map);
	tmp_map = map->raw_map;
	map->raw_map = ft_strjoin(map->raw_map, tmp_line);
	free(tmp_map);
	free(tmp_line);
	if (!map->raw_map)
		map_error(MALLOC_PARSE, &map);
	ft_ptr_free((void **)&map->line);
}

static void dfs_map(char **grid, int i, int j, t_map *map)
{
	size_t j_len;

	if (i < 0 || i > map->tokens || j < 0 || grid[i][j] == ' ')
		map_error(MAP_HOLE, &map);
	j_len = ft_strlen(grid[i]);
	j_len--;
	if (j > j_len)
		map_error(MAP_HOLE, &map);
	if (grid[i][j] == '1' || grid[i][j] == '3')
		return ;
	//if ((grid[i][j] == '2') && (!i || i == map->tokens || !j || j == j_len))
		//map_error(MAP_HOLE, &map);
	grid[i][j] = '3';
	dfs_map(grid, i - 1, j, map);
	dfs_map(grid, i, j - 1, map);
	dfs_map(grid, i + 1, j, map);
	dfs_map(grid, i, j + 1, map);
}

static void process_map(t_map *map)
{
	int reading;

	if (!ft_strinset(map->line, MAP_SET))
		map_error(UNKNOWN_CH_MAP, &map);
	map->raw_map = ft_strjoin(map->line , "\n");
	if (!map->raw_map)
		map_error(MALLOC_PARSE, &map);
	ft_ptr_free((void **)&map->line);
	map->tokens = 0; // rows
	while ((reading = get_next_line(map->fd, &(map->line))))
		get_raw_map(map, reading);
	get_raw_map(map, reading);
	if (!map->player[GET_ALL])
		map_error(NO_PLAYER, &map);
	map->map = ft_split(map->raw_map, '\n');
	ft_ptr_free((void **)&map->raw_map);
	dfs_map(map->map, map->player[X], map->player[Y], map);
	//map_error("Done", &map);
	map->map_done++;
}

static void	process_parsing(t_map *map)
{
	size_t first;

	map->split = ft_split(map->line, ' ');
	if (!map->split)
		map_error(MALLOC_PARSE, &map);
	map->tokens = ft_twodarr_len((void **)map->split);
	first = ft_strlen(map->split[0]); // len of first param
	process_line(map, first);
	ft_twodarr_free((void ***)&map->split, map->tokens);
	ft_ptr_free((void **)&map->line);
}

t_game	*parser(const char *map_file)
{
	t_map	*map;
	t_game	*game;
	int		reading;

	init_map(&map, map_file);
	while ((reading = get_next_line(map->fd, &(map->line))))
	{
		if (reading < 0)
			map_error(GNL_ERROR, &map);
		if (!(*map->line)) // empty line
			continue ;
		map_ready(map) ? process_map(map) : process_parsing(map);
	}
	if (!reading && !map->map_done)
		map_error(NO_MAP, &map);
	init_game(&game, map);
	return (game);
}

