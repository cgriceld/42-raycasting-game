#include "maze.h"

static void args_error_manager(const int code, const char *comment)
{
	ft_putendl_fd("Error", 1);
	if (code == ARGS)
		ft_putendl_fd(comment, 1);

}
