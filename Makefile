NAME = cub3D
HEADER = engine/maze.h
MLXDIR = mlx
SAVE = cub3D.bmp

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRC =	engine/entry_point.c engine/sort_sprites.c \
		engine/error_game.c engine/error_map.c engine/init_structs.c \
		engine/parser_config.c engine/parser_map.c engine/parser.c \
		engine/rays.c engine/steps.c engine/turns.c engine/play.c \
		engine/save.c engine/sprites.c \
		engine/utils/ft_split.c engine/utils/gnl_utils.c \
		engine/utils/gnl.c engine/utils/memory.c engine/utils/puts.c \
		engine/utils/search.c engine/utils/strings.c engine/utils/types.c \
		engine/utils/ft_strtrim.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
all : start $(NAME)

start:
	@echo "\033[1;35m WELCOME TO CUB3D! \033[0m"
	@echo "\033[1;35m LOADING... \033[0m"

$(NAME) : $(OBJ) $(HEADER)
	@make -C $(MLXDIR)
	@$(CC) $(CFLAGS) $(SRC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "\033[1;36m START GAME : ./cub3D *.cub [--save] \033[0m"

demo1: all
	@./cub3D maps/barrels.cub

demo2: all
	@./cub3D maps/spaces.cub

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[1;32m OBJECT FILES DELETED \033[0m"

fclean : clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(SAVE)
	#@make -C $(MLXDIR) clean
	@echo "\033[1;32m EXECUTABLE DELETED \033[0m"

re : fclean all

.PHONY:	all clean fclean re demo1 demo2