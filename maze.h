#ifndef MAZE_H
# define MAZE_H

# define true 1
# define false 0

# define DEFAULT_RES_X 5120
# define DEFAULT_RES_Y 2880

/*
** Input arguments errors.
*/
# define ARGS_NUM_COMMENT "Wrong number of arguments, try again: ./maze *.cub [--save]"
# define MAP_NAME_COMMENT "Check the extension of the map file, it should be .cub, or filename name is missing"
# define NEG_FD "Error encountered when try to open .cub file, try again"

/*
** Parsing errors.
*/
# define UNKNOWN_CH "Unknown symbols or wrong params in .cub file, check it and try again"
# define RES_ERR "Something wrong with resolution params in .cub, check it and try again"

/*
** Malloc errors.
*/
# define MALLOC_TMAP_INIT "Memory error encountered while parsing, try again"

#include "libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>

/*
** Struct for parsing.
*/
typedef struct	s_map
{
	int		fd;
	char	*line;
	char	**split;
	size_t	tokens;
	int		res_x;
	int		res_y;
}				t_map;

/*
** Struct for raycasting.
*/
typedef struct	s_person
{
	
}				t_person;

/*
** Struct for mlx stuff.
*/
typedef struct	s_mlx_manager
{
	void	*ptr;
	void	*window;
	void	*image;
	int		img_h;
	int		img_w;
}				t_mlx_manager;

// to libft
size_t		twodarr_len(void **arr);
size_t	ft_strlen(const char *s);
int	ft_strendcmp(const char *s1, const char *s2, int n);
void	parser(const char *map_file);
int lite_error(char *comment);
int map_error(char *comment, t_map **map);
int	init_map(t_map **map, const char *map_file);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int				get_next_line(int fd, char **line);
char		**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
int		ft_strdigits(char *str);

#endif