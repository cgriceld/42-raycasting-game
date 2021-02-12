#ifndef MAZE_H
# define MAZE_H

# include "../mlx/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 21
#endif

# define TITLE "maze"
# define MAP_SET " 012NSEW"
# define PLAYER_SET "NSEW"
# define NO_TRANSPARENT 0x00FFFFFF
# define TRUE 1
# define FALSE 0

/*
** Screenshot messages
*/
# define SAVED "saved, check out cub3D.bmp file"
# define WRITE_ERR ".bmp : write error while saving screenshot"
# define FD_ERR ".bmp : error when creating file, try again"

/*
** Input arguments errors
*/
# define ARGS_NUM_COMMENT "wrong number of arguments, try again: ./cub3D *.cub [--save]"
# define MAP_NAME_COMMENT "map file is wrong or missing (check the extension, order of arguments, etc.), try again"
# define SAVE_ERR "wrong --save option (check order of arguments), try again"
# define NEG_FD "error encountered when try to open .cub file (no file, etc.), try again"

/*
** Config parsing errors
*/
# define GNL_ERROR ".cub : error encountered while reading, try again"
# define UNKNOWN_CH ".cub : syntax error, unknown symbols, config missing before map, map not in the end, etc."
# define RES_ERR ".cub : error with R params (negative, zero or unknown symbols), try again"
# define RES_DOUBLE ".cub : two configurations for R, try again"
# define PATH_DOUBLE ".cub : two configurations for path (NO, WE, SO EA or S), try again"
# define INVALID_PATH ".cub : invalid path for wall or sprite texture, try again"
# define COLOR_DOUBLE ".cub : two configurations for F or C, try again"
# define COLOR_ERR ".cub : error with color params in F or C (negative, unknown symbols or delimiter isn't ','), try again"
# define COLOR_0255 ".cub : color params for F or C aren't in [0, 255] range, try again"

/*
** Map parsing errors
*/
# define NO_MAP "map .cub : map missing or consists of one line only, try again"
# define MAP_EMPTY_LINE "map .cub : it should be no empty lines inside or below the map, try again"
# define UNKNOWN_CH_MAP "map .cub : map should consists only from [ 012NSEW] characters, try again"
# define TWO_PLAYERS "map .cub : map contains two or more players ([NSEW] symbols), choose one and try again"
# define NO_PLAYER "map .cub : no player found in map, try again"
# define MAP_HOLE "map .cub : map isn't surrounded by walls or has spaces inside, try again"

/*
** Malloc errors
*/
# define MALLOC_PARSE "memory : malloc error encountered while parsing, try again"
# define MALLOC_GAME "memory : malloc error while rendering, try again"
# define MLX_MALLOC "mlx : malloc error while rendering, try again"

/*
** MLX errors
*/
# define MLX_INIT "mlx : mlx_init() returns NULL, try again"
# define MLX_NEWWIN "mlx : mlx_new_window() returns NULL, try again"
# define MLX_XPM "mlx : mlx_xpm_file_to_image() returns NULL, try again"
# define MLX_NEWIMG "mlx : mlx_new_image() returns NULL, try again"

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
# define SAVE 0b10000000
# define EMPTY 0b00000000

typedef struct		s_lstfd
{
	int				fd;
	char			*cache;
	struct s_lstfd	*next;
}					t_lstfd;

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
** mlx image struct
*/
typedef struct	s_mlximg
{
	void			*img;
	unsigned int	*data;
	int				bits_in_texel;
	int				bytes_line;
	int				little_endian;
	int				img_width;
	int				img_height;
}				t_mlximg;

/*
** Parsing struct
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
	int spritescreenx;
	int spriteh;
	int spritew;
}				t_spr;

/*
** Game struct
*/
typedef struct	s_game
{
	int			res[2];
	int			rows;
	t_mlximg	*maze;
	t_mlximg	**ttrs;
	char		**map;
	char		**paths;
	void		*mlx;
	void		*win;
	int			colors[2];
	double		pos[2];
	double		dir[2];
	double		plane[2];
	double		camerax;
	unsigned char			event;
	unsigned char			save;
	int			step[2];
	double		raydir[2];
	double		deltadist[2];
	double		perpwalldist;
	int			side;
	int			square[2];
	double		sidedist[2];
	char		side_hited;
	double		**sprites;
	int			numspr;
	double		*zbuffer;
	t_spr		*spr;
}				t_game;

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

void	parser(const char *map_file, t_game **game);
void free_map(t_map **map);
int maze(t_game *game);
int game_over(t_game **game);
void init_map(t_map **map, const char *map_file);
void init_game(t_game **game, t_map *map);
void process_line(t_map *map, size_t first);
void get_raw_map(t_map *map, int reading);
void dfs_map(char **grid, int i, int j, t_map *map);
void turn_left(t_game *game);
void turn_right(t_game *game);
void step_up(t_game *game);
void step_left(t_game *game);
void step_down(t_game *game);
void step_right(t_game *game);

void lite_error(char *comment);
void map_error(char *comment, t_map **map);
void free_game(t_game **game);
void game_error(char *comment, t_game **game);


int				klick(int key, t_game *game);
int				unclick(int key, t_game *game);
int			play(t_game *game);
void			player_update(t_game *s);
void		throw_rays(t_game *game);
void		slice(t_game *game, int start, int end, int lineheight, int ray);
void save(t_game *game);
int	ft_putstr_fd(const char *s, const int fd);
void sprites(t_game *game);
int		ft_numchstr(char *s, char ch);
void sort_sprites(t_game *game);

#endif
