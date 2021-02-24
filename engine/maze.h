#ifndef MAZE_H
# define MAZE_H

# include "../mlx/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define BUFFER_SIZE 21

# define TITLE "maze"
# define MAP_SET " 012NSEW"
# define PLAYER_SET "NSEW"
# define NO_TRANSPARENT 0x00FFFFFF
# define TRUE 1
# define FALSE 0

/*
** Screenshot stuff
*/
# define SAVED "saved, check out cub3D.bmp file"
# define WRITE_ERR ".bmp : write error while saving screenshot"
# define FD_ERR ".bmp : error when creating file"
# define SAVE 0b10000000

/*
** Input arguments errors
*/
# define ARGS_NUM_COMMENT "wrong arguments, must be: ./cub3D *.cub [--save]"
# define MAP_NAME_COMMENT "map file is wrong or missing"
# define SAVE_ERR "wrong --save option"
# define NEG_FD "error when try to open .cub file (no file, etc.)"

/*
** Config parsing errors
*/
# define GNL_ERROR ".cub : error encountered while reading"
# define UNKNOWN_CH ".cub : syntax error, unknown symbols, config missing, etc"
# define RES_ERR ".cub : error with R"
# define RES_DOUBLE ".cub : two configurations for R"
# define PATH_DOUBLE ".cub : two configurations for path (NO, EA, WE, SO, S)"
# define INVALID_PATH ".cub : invalid path for texture (NO, EA, WE, SO, S)"
# define COLOR_DOUBLE ".cub : two configurations for F or C"
# define COLOR_ERR ".cub : error with F or C params"
# define COLOR_0255 ".cub : F and C params must be in [0, 255] range"

/*
** Map parsing errors
*/
# define NO_MAP "map .cub : map missing or wrong or config missing"
# define MAP_EMPTY_LINE "map .cub : empty lines inside or below the map"
# define UNKNOWN_CH_MAP "map .cub : map must consists only of [ 012NSEW]"
# define TWO_PLAYERS "map .cub : map contains two or more players"
# define NO_PLAYER "map .cub : no player found in map"
# define MAP_HOLE "map .cub : map isn't surrounded by walls (or spaces inside)"

/*
** Malloc errors
*/
# define MALLOC_PARSE "memory : malloc error encountered while parsing"
# define MLX_MALLOC "mlx : malloc error while rendering"

/*
** MLX errors
*/
# define MLX_INIT "mlx : mlx_init() returns NULL"
# define MLX_NEWWIN "mlx : mlx_new_window() returns NULL"
# define MLX_XPM "mlx : mlx_xpm_file_to_image() returns NULL"
# define MLX_NEWIMG "mlx : mlx_new_image() returns NULL"

/*
** Events masks
*/
# define W 0b00000001
# define A 0b00000010
# define S 0b00000100
# define D 0b00001000
# define LEFT 0b00010000
# define RIGHT 0b00100000
# define INIT 0b01000000
# define EMPTY 0b00000000

typedef struct	s_lstfd
{
	int				fd;
	char			*cache;
	struct s_lstfd	*next;
}				t_lstfd;

typedef enum	e_texture
{
	NO,
	EA,
	SO,
	WE,
	SPRITE
}				t_texture;

typedef enum	e_color
{
	FLOOR,
	CEILING,
	GET_FLOOR,
	GET_CEILING
}				t_color;

typedef enum	e_person
{
	X,
	Y,
	GET_ALL
}				t_person;

/*
** mlx image struct
*/
typedef struct	s_mlximg
{
	void			*img;
	unsigned int	*data;
	int				img_width;
	int				img_height;
	int				bits_in_texel;
	int				bytes_line;
	int				little_endian;
}				t_mlximg;

/*
** Parsing struct, tokens = rows
*/
typedef struct	s_map
{
	int		fd;
	char	*line;
	char	**split;
	char	*raw_map;
	int		tokens;
	int		map_done;
	int		res[2];
	char	**paths;
	int		colors[4];
	char	**map;
	double	player[3];
	double	dir[2];
	double	plane[2];
	int		sprites;
}				t_map;

/*
** Sprite struct
*/
typedef struct	s_spr
{
	int wherex;
	int height;
	int width;
}				t_spr;

/*
** Game struct
*/
typedef struct	s_game
{
	int				res[2];
	int				rows;
	int				colors[2];
	int				dirmove[2];
	int				currside;
	int				square[2];
	int				numspr;
	int				wallstart;
	int				wallend;
	int				wallheight;
	t_mlximg		*maze;
	t_mlximg		**ttrs;
	char			**map;
	char			**paths;
	void			*mlx;
	void			*win;
	double			player[2];
	double			dir[2];
	double			plane[2];
	double			ray[2];
	double			next[2];
	double			dist;
	double			path[2];
	double			**sprites;
	double			*depth;
	t_spr			*spr;
	unsigned char	event;
	unsigned char	save;
}				t_game;

/*
** Parser
*/
void			parser(const char *map_file, t_game **game);
void			process_line(t_map *map, size_t first);
int				cht(char **colors, size_t tokens);
void			get_raw_map(t_map *map, int reading);
void			find_player(t_map *map);
void			dfs_all(t_map *map);
void			init_map(t_map **map, const char *map_file);
void			init_game(t_game **game, t_map *map);

/*
** Errors
*/
void			lite_error(char *comment);
void			free_map(t_map **map);
void			map_error(char *comment, t_map **map);
void			free_game(t_game **game);
void			game_error(char *comment, t_game **game);
int				game_over(t_game **game);

/*
** Play
*/
int				klick(int key, t_game *game);
int				unclick(int key, t_game *game);
int				play(t_game *game);
void			step_up(t_game *game);
void			step_left(t_game *game);
void			step_down(t_game *game);
void			step_right(t_game *game);
void			turn_right(t_game *game);
void			turn_left(t_game *game);
void			throw_rays(t_game *game);
void			sort_sprites(t_game *game);
void			sprites(t_game *game);
void			save(t_game *game);

/*
** Utils
*/
int				get_next_line(int fd, char **line);
int				subcache(char **cache, char *n);
char			*nchr(const char *s);
int				lstdelone(t_lstfd **head, const int fd);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strendcmp(const char *s1, const char *s2, int n);
char			*ft_strchr(const char *s, int c);
char			*ft_strchrset(char *s, char *set);
int				ft_strinset(char *s, char *set);
int				ft_numchstr(char *s, char ch);
void			ft_ptr_free(void **ptr);
size_t			ft_twodarr_len(void **arr);
void			ft_twodarr_free(void ***arr, int len);
int				ft_isdigit(int c);
int				ft_strdigits(char *str);
int				ft_atoi(const char *str);
void			ft_putendl_fd(char *s, int fd);

#endif
