#include <stdlib.h>
#include <stdio.h>

int		create_trgb(int t, int r, int g, int b)
{
	// *color = r;
	// *color = (*color << 8) + g;
	// *color = (*color << 8) + b;
	return(t << 24 | r << 16 | g << 8 | b);
}
int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}


int main(void)
{
	// int color;
	// create_trgb(0, 225, 225, 225, &color);

	int color = create_trgb(0, 0, 0, 0);

	printf("%d\n", get_t(color));
	printf("%d\n", get_r(color));
	printf("%d\n", get_g(color));
	printf("%d\n", get_b(color));
	return (0);
}