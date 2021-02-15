/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:20:11 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/15 22:33:22 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

/*
**  ——————————> X
** |     ^ N
** | W   |
** | <---|---> E
** |     |
** |       S
** ^ Y
*/

static void	player_sw(char *player, t_map *map)
{
	if (*player == 'S')
	{
		map->dir[X] = 0;
		map->dir[Y] = 1;
		map->plane[X] = -0.66;
		map->plane[Y] = 0;
	}
	else if (*player == 'W')
	{
		map->dir[X] = -1;
		map->dir[Y] = 0;
		map->plane[X] = 0;
		map->plane[Y] = -0.66;
	}
	map->player[GET_ALL]++;
}

static void	find_player(t_map *map)
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
		player_sw(player, map);
	}
}

void		get_raw_map(t_map *map, int reading)
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
	map->sprites += ft_numchstr(map->line, '2');
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

void		dfs_map(char **grid, int i, int j, t_map *map)
{
	int j_len;

	if (i < 0 || i > map->tokens || j < 0 || grid[i][j] == ' ')
		map_error(MAP_HOLE, &map);
	j_len = (int)ft_strlen(grid[i]);
	j_len--;
	if (j > j_len)
		map_error(MAP_HOLE, &map);
	if (grid[i][j] == '1' || grid[i][j] == '3' || grid[i][j] == '4')
		return ;
	if (grid[i][j] == '2')
		grid[i][j] = '4';
	if (grid[i][j] == '0')
		grid[i][j] = '3';
	dfs_map(grid, i - 1, j, map);
	dfs_map(grid, i, j - 1, map);
	dfs_map(grid, i + 1, j, map);
	dfs_map(grid, i, j + 1, map);
}
