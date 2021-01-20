#include <stdio.h>
#include <stdlib.h>

void get(char ***map, int size)
{
	char **tmp = *map;
	while (size--)
	{
		if (tmp[size])
			free(tmp[size]);
	}
	free(tmp);
	*map = NULL;
}

int main(void)
{
	int size = 2;

	char **map = (char **)malloc(sizeof(char *) * size);
	map[0] = (char *)malloc(1);
	map[1] = (char *)malloc(1);
	get(&map, size);
	if (map == NULL)
		printf("%s\n", "null");

	return (0);
}