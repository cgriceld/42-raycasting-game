/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:38:25 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/19 12:52:09 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

static void	free_mlximg(t_game **game, int len)
{
	while (len--)
	{
		if ((*game)->ttrs[len] && (*game)->ttrs[len]->img)
		{
			mlx_destroy_image((*game)->mlx, (*game)->ttrs[len]->img);
			free((*game)->ttrs[len]);
		}
	}
	free((*game)->ttrs);
}

void		free_game(t_game **game)
{
	if ((*game)->map)
		ft_twodarr_free((void ***)&(*game)->map, ++(*game)->rows);
	if ((*game)->paths)
		ft_twodarr_free((void ***)&(*game)->paths, 5);
	if ((*game)->sprites)
		ft_twodarr_free((void ***)&(*game)->sprites, (*game)->numspr);
	if ((*game)->ttrs)
		free_mlximg(game, 5);
	if ((*game)->maze && (*game)->maze->img)
	{
		mlx_destroy_image((*game)->mlx, (*game)->maze->img);
		free((*game)->maze);
	}
	if ((*game)->win)
		mlx_destroy_window((*game)->mlx, (*game)->win);
	if ((*game)->depth)
		free((*game)->depth);
	if ((*game)->spr)
		free((*game)->spr);
	free(*game);
}

void		game_error(char *comment, t_game **game)
{
	free_game(game);
	lite_error(comment);
}

int			game_over(t_game **game)
{
	(*game)->save & SAVE ? ft_putendl_fd(SAVED, 1) : \
						ft_putendl_fd("GAME OVER", 1);
	free_game(game);
	// while (1)
	// 	;
	exit(EXIT_SUCCESS);
}
