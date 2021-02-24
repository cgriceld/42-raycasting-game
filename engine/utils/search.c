#include "../maze.h"

char	*ft_strchr(const char *s, int c)
{
	char ch;

	ch = (char)c;
	while (*s && *s != ch)
		s++;
	return (*s == ch ? (char *)s : NULL);
}

char	*ft_strchrset(char *s, char *set)
{
	char *tmp;

	tmp = s;
	while (*s && !ft_strchr(set, *s))
		s++;
	return (!*s ? NULL : s);
}

int		ft_strinset(char *s, char *set)
{
	while (*s && ft_strchr(set, *s))
		s++;
	return (!*s ? 1 : 0);
}

int		ft_numchstr(char *s, char ch)
{
	int i;

	i = 0;
	while (*s)
	{
		if (*s++ == ch)
			i++;
	}
	return (i);
}
