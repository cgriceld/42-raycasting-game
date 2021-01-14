#ifndef MAZE_H
# define MAZE_H

# define TRUE 1
# define FALSE 0

/*
** Input arguments errors
*/
# define ARGS 0
# define ARGS_NUM_COMMENT "Wrong number of arguments, try again: ./maze *.cub [--save]"
# define MAP_NAME_COMMENT "Check the extension of the map file, it should be .cub"

#include "libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>

typedef struct	s_person
{
	int error;
}				t_person;

typedef struct	s_mlx_manager
{
	void	*ptr;
	void	*window;
	void	*image;
	int		img_h;
	int		img_w;
}				t_mlx_manager;

#endif