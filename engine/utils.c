#include "maze.h"

//to libft
void	ft_ptr_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	*ft_strchr(const char *s, int c)
{
	char ch;

	ch = (char)c;
	while (*s && *s != ch)
		s++;
	return (*s == ch ? (char *)s : NULL);
}

//to libft, same to ft_strchr, only it
char		*ft_strchrset(char *s, char *set)
{
	char *tmp;

	tmp = s;
	while (*s && !ft_strchr(set, *s))
		s++;
	return (!*s ? NULL : s);
}

//to libft
size_t		ft_twodarr_len(void **arr)
{
	size_t len;

	len = 0;
	while (*arr++)
		len++;
	return (len);
}

//to libft
void		ft_twodarr_free(void ***arr, int len)
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

//to libft, check if all string consists only of characters from set
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

size_t	ft_strlen(const char *s)
{
	const char *str;

	str = s;
	while (*str)
		str++;
	return (str - s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	tmp = join;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (join);
}

char	*ft_strdup(const char *s1)
{
	char *dup;
	char *tmp;

	dup = (char *)malloc(ft_strlen(s1) + 1);
	if (!dup)
		return (NULL);
	tmp = dup;
	while (*s1)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (dup);
}

int	ft_strendcmp(const char *s1, const char *s2, int n)
{
	while (n--)
		s1++;
	while (*s1)
	{
		if (*s1++ != *s2++)
			return (1);
	}
	return (0);
}

int		lstdelone(t_lstfd **head, const int fd)
{
	t_lstfd *tmp;
	t_lstfd *previous;

	tmp = *head;
	if (tmp->fd == fd)
	{
		*head = tmp->next;
		if (tmp->cache)
			free(tmp->cache);
		free(tmp);
		return (0);
	}
	while (tmp->fd != fd)
	{
		previous = tmp;
		tmp = tmp->next;
	}
	previous->next = tmp->next;
	if (tmp->cache)
		free(tmp->cache);
	free(tmp);
	return (0);
}

char	*nchr(const char *s)
{
	while (*s && *s != '\n')
		s++;
	return (*s == '\n' ? (char *)s : NULL);
}

int		subcache(char **cache, char *n)
{
	char *subcache;

	subcache = ft_strdup(n);
	if (!subcache)
		return (0);
	free(*cache);
	*cache = subcache;
	return (1);
}


static int		lstclear(t_lstfd **head, char **line)
{
	t_lstfd *tmp;

	if (*line)
		free(*line);
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->cache)
			free(tmp->cache);
		free(tmp);
	}
	return (-1);
}

static t_lstfd	*lstfdnew(const int fd)
{
	t_lstfd	*newnode;

	newnode = (t_lstfd *)malloc(sizeof(t_lstfd));
	if (!newnode)
		return (NULL);
	newnode->fd = fd;
	newnode->cache = NULL;
	newnode->next = NULL;
	return (newnode);
}

static void		check_cache(t_lstfd *tmp, char **line, int *flag)
{
	char *n;

	if (!(tmp->cache))
		return ;
	free(*line);
	if ((n = nchr(tmp->cache)))
	{
		*n++ = '\0';
		*flag = (!(*line = ft_strdup(tmp->cache)) || \
				!subcache(&(tmp->cache), n)) ? -1 : 1;
		return ;
	}
	*line = ft_strdup(tmp->cache);
	if (!*line)
		*flag = -1;
	free(tmp->cache);
	tmp->cache = NULL;
}

static void		process_buff(char *buff, char **line, t_lstfd *tmp, int *flag)
{
	ssize_t	bytes_read;
	char	*n;
	char	*tmpline;

	check_cache(tmp, line, flag);
	bytes_read = 0;
	while (!*flag && (bytes_read = read(tmp->fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes_read] = '\0';
		if ((n = nchr(buff)))
		{
			*n++ = '\0';
			*flag = !(tmp->cache = ft_strdup(n)) ? -1 : 1;
			if (*flag < 0)
				return;
		}
		tmpline = *line;
		*line = ft_strjoin(*line, buff);
		if (!*line)
			*flag = -1;
		free(tmpline);
	}
	*flag = (bytes_read < 0) ? -1 : *flag;
}

int				get_next_line(int fd, char **line)
{
	static t_lstfd	*head;
	t_lstfd			*tmp;
	char			*buff;
	int				flag;

	if (BUFFER_SIZE <= 0 || fd < 0 || !line || \
		(!head && !(head = lstfdnew(fd))))
		return (-1);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (!(tmp->next) && !(tmp->next = lstfdnew(fd)))
			return (lstclear(&head, NULL));
		tmp = tmp->next;
	}
	if (!(buff = (char *)malloc(BUFFER_SIZE + 1)))
		return (lstclear(&head, NULL));
	flag = 0;
	if (!(*line = ft_strdup("")))
		return (lstclear(&head, NULL));
	process_buff(buff, line, tmp, &flag);
	free(buff);
	if (flag)
		return (flag == 1 ? flag : lstclear(&head, line));
	return (lstdelone(&head, tmp->fd));
}

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char *str1;
	unsigned char		*str2;

	if ((s1 && (s1 == s2)) || !n)
		return (0);
	str1 = (const unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n-- && (*str1 || *str2))
	{
		if (*str1++ != *str2++)
			return (*(--str1) - *(--str2));
	}
	return (0);
}

int	ft_putstr_fd(const char *s, const int fd)
{
	if (fd >= 0 && s)
	{
		if (write(fd, s, ft_strlen(s)) < 0)
			return (-1);
		return (1);
	}
	return (-1);
}

int	ft_putchar_fd(const char c, const int fd)
{
	if (fd >= 0)
	{
		if (write(fd, &c, 1) < 0)
			return (-1);
		return (1);
	}
	return (-1);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (fd >= 0 && s)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

// to libft
int		ft_strdigits(char *str)
{
	while (*str && ft_isdigit(*str))
		str++;
	return (!*str ? 1 : 0);
}

static int	ft_issign(const char c)
{
	return (c == 43 || c == 45);
}

/*
** Returns 1 if c is \t, \n, \v, \f, \r or ' '.
*/

static int	ft_isspace(const char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int			ft_atoi(const char *str)
{
	long long int	prevn;
	long long int	n;
	int				sign;

	n = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (ft_issign(*str) && *str++ == '-')
		sign = -1;
	while (*str && ft_isdigit(*str))
	{
		prevn = n;
		n = 10 * n + sign * (*str++ - 48); //*
		if (n > prevn && sign == -1) //**
			return (0);
		if (n < prevn && sign == 1)
			return (-1);
	}
	return (n);
}