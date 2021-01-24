#include <stdlib.h>

struct game
{
	char *s;
};

int main(void)
{
	struct game *g;
	char *test;

	g = (struct game *)malloc(sizeof(struct game));
	g->s = (char *)malloc(1);
	*(g->s) = 's';
	test = g->s;
	g->s = NULL;
	free(g);
	free(test);

	return (0);
}