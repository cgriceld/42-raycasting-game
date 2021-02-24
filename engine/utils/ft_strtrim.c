#include "../maze.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		sublen;
	char const	*substart;
	char		*substr;
	char		*tmp;

	if (!s)
		return (NULL);
	while (start-- && *s)
		s++;
	substart = s;
	while (len-- && *s)
		s++;
	sublen = s - substart;
	substr = (char *)malloc(sublen + 1);
	if (!substr)
		return (NULL);
	tmp = substr;
	while (sublen--)
		*tmp++ = *substart++;
	*tmp = '\0';
	return (substr);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char const *trimstart;

	if (!s1 || !set)
		return (NULL);
	if (!*set || !*s1)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	trimstart = s1;
	while (*s1)
		s1++;
	while (s1 != trimstart && ft_strchr(set, *s1))
		s1--;
	return (ft_substr(trimstart, 0, s1 - trimstart + 1));
}
