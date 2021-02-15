/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:50:44 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/15 16:51:14 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../maze.h"

void	ft_ptr_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

size_t	ft_twodarr_len(void **arr)
{
	size_t len;

	len = 0;
	while (*arr++)
		len++;
	return (len);
}

void	ft_twodarr_free(void ***arr, int len)
{
	void **tmp;

	tmp = *arr;
	while (len--)
	{
		if (tmp[len])
			free(tmp[len]);
	}
	free(tmp);
	*arr = NULL;
}
