#include "maze.h"

int	main(int argc, char **agrv)
{
	if (argc == 3)
		save();
	else if (argc == 2)
		parse();
	
	return (0);
}