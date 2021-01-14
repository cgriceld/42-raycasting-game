#include "mlx/mlx.h"
#include <stdio.h>

typedef struct	s_data
{
	int bpp; /// 32b = 4B to represent a pixel color
	int bytes_line; // 2048B to store one line of image in memory
	int endian; // little endian, 7-6-5-4-3-2-1-0
}				t_data;


int	main(void)
{
	void *mlx;
	void *mlx_win;
	void *img;
	char *addr; // begining of the memory area where the image is stored
	int x = 200;
	int y = 200;
	int color = 0xFFFF00;
	t_data test;
	char *dst;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
	img = mlx_new_image(mlx, 500, 500);
	addr = mlx_get_data_addr(img, &test.bpp, &test.bytes_line, &test.endian);
	while (x++ < 300)
	{
		y = 200;
		while (y++ < 300)
		{
			dst = addr + (y * test.bytes_line + x * (test.bpp / 8));
			*(unsigned int *)dst = color;
		}
	}

	mlx_put_image_to_window(mlx, mlx_win, img, 0, 0);

	printf("%d\n", test.bpp);
	printf("%d\n", test.bytes_line);
	printf("%d\n", test.endian);

	mlx_loop(mlx);
	return (0);
}