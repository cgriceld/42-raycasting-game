#include <stdio.h>
#include <stdlib.h>

void get(char *map)
{
	map = NULL;
}

int main(void)
{
	int size = 2;

	char **map = (char **)malloc(sizeof(char *) * size);
	map[0] = (char *)malloc(1);
	map[1] = (char *)malloc(1);
	get(map[0]);
	if (!map[0])
		printf("%s\n", "null");

	return (0);
}