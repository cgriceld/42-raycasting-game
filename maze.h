#ifndef MAZE_H
# define MAZE_H

# define true 1
# define false 0

/*
** Input arguments errors.
*/
# define ARGS_NUM_COMMENT "Wrong number of arguments, try again: ./maze *.cub [--save]"
# define MAP_NAME_COMMENT "Check the extension of the map file, it should be .cub"
# define NEG_FD "Error encountered when try to open .cub file, try again"

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
	int fd;
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

#endif