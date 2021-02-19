/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:19:49 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/19 12:20:57 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"
#include <stdio.h>

static int	map_ready(t_map *map)
{
	return (map->res[X] && map->paths[NO] && map->paths[EA] && \
			map->paths[SO] && map->paths[WE] && map->paths[SPRITE] && \
			map->colors[GET_FLOOR] && map->colors[GET_CEILING]);
}

static void	process_map(t_map *map)
{
	int reading;

	if (!ft_strinset(map->line, MAP_SET))
		map_error(UNKNOWN_CH_MAP, &map);
	map->raw_map = ft_strjoin(map->line, "\n");
	if (!map->raw_map)
		map_error(MALLOC_PARSE, &map);
	find_player(map);
	map->sprites += ft_numchstr(map->line, '2');
	map->tokens = 0;
	ft_ptr_free((void **)&map->line);
	while ((reading = get_next_line(map->fd, &(map->line))))
		get_raw_map(map, reading);
	get_raw_map(map, reading);
	if (!map->player[GET_ALL])
		map_error(NO_PLAYER, &map);
	map->map = ft_split(map->raw_map, '\n');
	ft_ptr_free((void **)&map->raw_map);
	dfs_all(map);
	map->map_done++;

	// int tmp = map->tokens;
	// while (tmp >= 0)
	// {
	// 	printf("%s\n", map->map[tmp]);
	// 	tmp--;
	// }
}

static void	process_parsing(t_map *map)
{
	size_t first;

	map->split = ft_split(map->line, ' ');
	if (!map->split)
		map_error(MALLOC_PARSE, &map);
	map->tokens = (int)ft_twodarr_len((void **)map->split);
	if (!map->tokens)
		map_error(UNKNOWN_CH, &map);
	first = ft_strlen(map->split[0]);
	process_line(map, first);
	ft_twodarr_free((void ***)&map->split, map->tokens);
	ft_ptr_free((void **)&map->line);
}

void		parser(const char *map_file, t_game **game)
{
	t_map	*map;
	int		reading;

	init_map(&map, map_file);
	while ((reading = get_next_line(map->fd, &(map->line))))
	{
		if (reading < 0)
			map_error(GNL_ERROR, &map);
		if (!(*map->line))
		{
			ft_ptr_free((void **)&map->line);
			continue ;
		}
		map_ready(map) ? process_map(map) : process_parsing(map);
	}
	ft_ptr_free((void **)&map->line);
	if (!reading && !map->map_done)
		map_error(NO_MAP, &map);
	init_game(game, map);
}
