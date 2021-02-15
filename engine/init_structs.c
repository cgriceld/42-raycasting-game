/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:27:43 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/15 19:05:51 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

void		init_map(t_map **map, const char *map_file)
{
	*map = (t_map *)malloc(sizeof(t_map));
	if (!*map)
		lite_error(MALLOC_PARSE);
	(*map)->line = NULL;
	(*map)->split = NULL;
	(*map)->raw_map = NULL;
	(*map)->map = NULL;
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
	(*map)->colors[GET_FLOOR] = 0;
	(*map)->colors[GET_CEILING] = 0;
	(*map)->player[GET_ALL] = 0;
	(*map)->res[X] = 0;
	(*map)->map_done = 0;
	(*map)->sprites = 0;
}

static void	get_sprites(t_game **game)
{
	char	*line;
	int		rows;
	int		num;

	rows = (*game)->rows;
	num = (*game)->numspr;
	num--;
	while (--rows)
	{
		line = (*game)->map[rows];
		while (*line)
		{
			if (*line == '4')
			{
				(*game)->sprites[num] = (double *)malloc(sizeof(double) * 2);
				if (!(*game)->sprites[num])
					game_error(MLX_MALLOC, game);
				(*game)->sprites[num][X] = line - (*game)->map[rows] + 0.5;
				(*game)->sprites[num][Y] = rows + 0.5;
				num--;
			}
			line++;
		}
	}
}

static void	malloc_game(t_game **game, t_map *map)
{
	(*game)->depth = (double *)malloc(sizeof(double) * map->res[X]);
	if (!(*game)->depth)
	{
		free_map(&map);
		game_error(MLX_MALLOC, game);
	}
	(*game)->ttrs = (t_mlximg **)malloc(sizeof(t_mlximg *) * 5);
	if (!(*game)->ttrs)
	{
		free_map(&map);
		game_error(MLX_MALLOC, game);
	}
	if (map->sprites)
		(*game)->sprites = (double **)malloc(sizeof(double *) * map->sprites);
	if (!(*game)->sprites && map->sprites)
	{
		free_map(&map);
		game_error(MLX_MALLOC, game);
	}
	(*game)->spr = (t_spr *)malloc(sizeof(t_spr));
	if (!(*game)->spr)
	{
		free_map(&map);
		game_error(MLX_MALLOC, game);
	}
}

static void	copy_map(t_game **game, t_map *map)
{
	(*game)->res[X] = map->res[X];
	(*game)->res[Y] = map->res[Y];
	(*game)->colors[FLOOR] = map->colors[FLOOR];
	(*game)->colors[CEILING] = map->colors[CEILING];
	(*game)->player[X] = map->player[Y];
	(*game)->player[Y] = map->player[X];
	(*game)->dir[X] = map->dir[X];
	(*game)->dir[Y] = map->dir[Y];
	(*game)->plane[X] = map->plane[X];
	(*game)->plane[Y] = map->plane[Y];
	free_map(&map);
}

void		init_game(t_game **game, t_map *map)
{
	*game = (t_game *)malloc(sizeof(t_game));
	if (!*game)
		map_error(MLX_MALLOC, &map);
	(*game)->paths = map->paths;
	map->paths = NULL;
	(*game)->map = map->map;
	map->map = NULL;
	(*game)->win = NULL;
	(*game)->maze = NULL;
	(*game)->sprites = NULL;
	(*game)->depth = NULL;
	(*game)->spr = NULL;
	(*game)->numspr = map->sprites;
	(*game)->rows = map->tokens;
	(*game)->event = INIT;
	malloc_game(game, map);
	copy_map(game, map);
	if ((*game)->numspr)
		get_sprites(game);
	(*game)->ttrs[NO] = NULL;
	(*game)->ttrs[EA] = NULL;
	(*game)->ttrs[SO] = NULL;
	(*game)->ttrs[WE] = NULL;
	(*game)->ttrs[SPRITE] = NULL;
}
