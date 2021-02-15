/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:55:26 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/15 16:56:40 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../maze.h"

static int	ft_putstr_fd(const char *s, const int fd)
{
	if (fd >= 0 && s)
	{
		if (write(fd, s, ft_strlen(s)) < 0)
			return (-1);
		return (1);
	}
	return (-1);
}

static int	ft_putchar_fd(const char c, const int fd)
{
	if (fd >= 0)
	{
		if (write(fd, &c, 1) < 0)
			return (-1);
		return (1);
	}
	return (-1);
}

void		ft_putendl_fd(char *s, int fd)
{
	if (fd >= 0 && s)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}
