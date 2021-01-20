#ifndef MAZE_H
# define MAZE_H

# define true 1
# define false 0

# define DEFAULT_RES_X 5120
# define DEFAULT_RES_Y 2880
# define MAP_SET " 012NSEW"

/*
** Input arguments errors.
*/
# define ARGS_NUM_COMMENT "Wrong number of arguments, try again: ./maze *.cub [--save]"
# define MAP_NAME_COMMENT "Check the extension of the map file, it should be .cub, or filename name is missing"
# define NEG_FD "Error encountered when try to open .cub file, try again"

/*
** Config parsing errors.
*/
# define GNL_ERROR "Error encountered while reading .cub file, try again"
# define UNKNOWN_CH "Syntax error in .cub file: unknown symbols, config missing before map, map not in the end, etc."
# define RES_ERR "Error with R params in .cub file (negative, zero or unknown symbols), try again"
# define RES_DOUBLE "Two configurations for R in .cub file, try again"
# define PATH_DOUBLE "Two configurations for path (NO, WE, SO EA or S) in .cub file, try again"
# define INVALID_PATH "Invalid path for texture in .cub file, try again"
# define COLOR_DOUBLE "Two configurations for F or C in .cub file, try again"
# define COLOR_ERR "Error with color params in F or C (negative, unknown symbols or delimiter isn't ','), try again"
# define COLOR_0255 "Color params for F or C aren't in [0, 255] range, try again"
# define NO_MAP "Map missing in .cub file or consists of one line only, try again"

/*
** Map parsing errors.
*/
# define MAP_EMPTY_LINE "It should be no empty lines inside or below the map in .cub, try again"
# define UNKNOWN_CH_MAP "Map should consists only from [ 012NSEW] characters, try again"

/*
** Malloc errors.
*/
# define MALLOC_PARSE "Memory error encountered while parsing, try again"

#include "libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>

typedef enum e_ttr
{
	NO,
	EA,
	SO,
	WE,
	SPRITE
}			t_ttr;

typedef enum e_clr
{
	GET_ALL,
	FLOOR,
	CEILING
}			t_clr;

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
	char	**paths;
	int		colors[3];
	int		reading;
	char	*raw_map;
	int		map_done;
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
void		twodarr_free(void **arr, int len);
size_t	ft_strlen(const char *s);
int	ft_strendcmp(const char *s1, const char *s2, int n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int				get_next_line(int fd, char **line);
char		**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
int		ft_strdigits(char *str);
int	ft_isdigit(int c);
int			ft_atoi(const char *str);
int		ft_strchset(char *s, char *set);
char	*ft_strchr(const char *s, int c);

void	init_map(t_map **map, const char *map_file);
void	parser(const char *map_file);


void lite_error(char *comment);
void map_error(char *comment, t_map **map);

#endif