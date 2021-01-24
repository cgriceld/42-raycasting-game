#ifndef MAZE_H
# define MAZE_H

# define TITLE "maze"
# define MAP_SET " 012NSEW"
# define PLAYER_SET "NSEW"

/*
** Input arguments errors.
*/
# define ARGS_NUM_COMMENT "wrong number of arguments, try again: ./maze *.cub [--save]"
# define MAP_NAME_COMMENT "check the extension of the map file, it should be .cub, or filename name is missing"
# define NEG_FD "error encountered when try to open .cub file, try again"

/*
** Config parsing errors.
*/
# define GNL_ERROR ".cub : error encountered while reading, try again"
# define UNKNOWN_CH ".cub : syntax error, unknown symbols, config missing before map, map not in the end, etc."
# define RES_ERR ".cub : error with R params (negative, zero or unknown symbols), try again"
# define RES_DOUBLE ".cub : two configurations for R, try again"
# define PATH_DOUBLE ".cub : two configurations for path (NO, WE, SO EA or S), try again"
# define INVALID_PATH ".cub : invalid path for texture, try again"
# define COLOR_DOUBLE ".cub : two configurations for F or C, try again"
# define COLOR_ERR ".cub : error with color params in F or C (negative, unknown symbols or delimiter isn't ','), try again"
# define COLOR_0255 ".cub : color params for F or C aren't in [0, 255] range, try again"

/*
** Map parsing errors.
*/
# define NO_MAP "map .cub : map missing or consists of one line only, try again"
# define MAP_EMPTY_LINE "map .cub : it should be no empty lines inside or below the map, try again"
# define UNKNOWN_CH_MAP "map .cub : map should consists only from [ 012NSEW] characters, try again"
# define TWO_PLAYERS "map .cub : map contains two or more players ([NSEW] symbols), choose one and try again"
# define NO_PLAYER "map .cub : no player found in map, try again"
# define MAP_HOLE "map .cub : map isn't surrounded by walls or has spaces inside, try again"

/*
** Malloc errors.
*/
# define MALLOC_PARSE "memory : malloc error encountered while parsing, try again"
# define MALLOC_GAME "memory : malloc error when starting game, try again"

/*
** MLX errors.
*/
# define MLX_INIT "mlx : mlx_init() returns NULL, try again"
# define MLX_NEWWIN "mlx : mlx_new_window() returns NULL, try again"

#include "libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>

typedef enum e_texture
{
	NO,
	EA,
	SO,
	WE,
	SPRITE
}			t_texture;

typedef enum e_color
{
	FLOOR,
	CEILING,
	GET_FLOOR,
	GET_CEILING
}			t_color;

typedef enum e_person
{
	X,
	Y,
	GET_ALL
}			t_person;

/*
** Struct for parsing.
*/
typedef struct	s_map
{
	int		fd;
	char	*line;
	char	**split;
	char	*raw_map;
	size_t	tokens;
	int		map_done;
	int		res[2];
	char	**paths;
	int		colors[4];
	char	**map;
	double	player[3];
	double	dir[2];
	double	plane[2];
}				t_map;

/*
** Struct for rendering.
*/
typedef struct	s_game
{
	void	*mlx;
	void	*win;
	int		res[2];
	char	**paths;
	int		colors[2];
	char	**map;
	size_t	rows;
	double	player[2];
	double	dir[2];
	double	plane[2];
	double	ray; // cameraX
}				t_game;

/*
** Struct for mlx image.
*/
typedef struct	s_mlximg
{
	void	*img;
	void	*window;
	void	*image;
	int		img_h;
	int		img_w;
}				t_mlximg;

// libft
size_t		ft_twodarr_len(void **arr);
void		ft_twodarr_free(void ***arr, int len);
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
int		ft_strinset(char *s, char *set);
char	*ft_strchr(const char *s, int c);
void	ft_ptr_free(void **ptr);
char		*ft_strchrset(char *s, char *set);

void	init_game(t_game **game, t_map *map);
void	init_map(t_map **map, const char *map_file);
t_game	*parser(const char *map_file);
void free_map(t_map **map);

void lite_error(char *comment);
void map_error(char *comment, t_map **map);
void free_game(t_game **game);
void game_error(char *comment, t_game **game);

#endif