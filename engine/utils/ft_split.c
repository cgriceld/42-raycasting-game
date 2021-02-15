/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:32:47 by cgriceld          #+#    #+#             */
/*   Updated: 2021/02/15 16:38:20 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../maze.h"

static int	ft_getwords(char const *s, const char c)
{
	int words;

	words = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s++ != c)
			words++;
		while (*s && *s != c)
			s++;
	}
	return (words);
}

static void	ft_copyword(char *dst, const char *src, size_t letters)
{
	while (--letters)
		*dst++ = *src++;
	*dst = '\0';
}

static int	ft_putwords(char const *s, char c, int words, char **split)
{
	char const	*start;
	int			w;
	size_t		letters;

	w = 0;
	while (words--)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		letters = s - start;
		split[w] = (char *)malloc(letters + 1);
		if (!split[w])
			return (w);
		ft_copyword(split[w++], start, letters + 1);
	}
	return (0);
}

char		**ft_split(char const *s, char c)
{
	int		words;
	int		error;
	char	**split;

	if (!s)
		return (NULL);
	words = ft_getwords(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	split[words] = NULL;
	error = ft_putwords(s, c, words, split);
	if (!error)
		return (split);
	while (error--)
		free(split[error]);
	free(split);
	return (NULL);
}
