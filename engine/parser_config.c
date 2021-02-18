/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:20:00 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/18 19:32:04 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

static void	parse_resolution(t_map *map)
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

static void	parse_ttr(t_map *map, int side)
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

static int	get_rgb(int red, int green, int blue)
{
	return ((red <= 255 && red >= 0 && green <= 255 && green >= 0 \
			&& blue <= 255 && blue >= 0) ? \
	(red << 16 | green << 8 | blue) : -1);
}

static int	check_t(char **colors, size_t tokens)
{
	char *tmp;

	while (tokens--)
	{
		tmp = ft_strtrim(colors[tokens], " ");
		if (!tmp)
			return (1);
		if (!*tmp || !ft_strdigits(tmp))
		{
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

static void	parse_color(t_map *map, int side)
{
	char	**colors;
	char	*start;
	size_t	tokens;

	if ((side == FLOOR && map->colors[GET_FLOOR]) || \
		(side == CEILING && map->colors[GET_CEILING]))
		map_error(COLOR_DOUBLE, &map);
	if (ft_numchstr(map->line, ',') != 2)
		map_error(COLOR_ERR, &map);
	start = side == FLOOR ? ft_strchr(map->line, 'F') : \
							ft_strchr(map->line, 'C');
	colors = ft_split(++start, ',');
	if (!colors)
		map_error(MALLOC_PARSE, &map);
	if ((tokens = ft_twodarr_len((void **)colors)) != 3 || check_t(colors, tokens))
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
}

void		process_line(t_map *map, size_t first)
{
	if (first == 1 && map->tokens == 3 && map->split[0][0] == 'R')
		parse_resolution(map);
	else if (first == 1)
	{
		if (map->tokens == 2 && map->split[0][0] == 'S')
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
