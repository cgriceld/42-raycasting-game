NAME = cub3D
HEADER = engine/maze.h

CC = gcc
CFLAGS = -g
#-Wall -Wextra -Werror

SRC =	engine/entry-point.c engine/sort_sprites.c \
		engine/error-managers.c engine/init-structs.c \
		engine/parser-config.c engine/parser-map.c engine/parser.c \
		engine/rays.c engine/steps.c engine/turns.c engine/play.c \
		engine/utils.c engine/save.c engine/sprites.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
all : start $(NAME)

start:
	@echo "\033[1;35m WELCOME TO CUB3D! \033[0m"
	@echo "\033[1;35m LOADING... \033[0m"

$(NAME) : $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(SRC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "\033[1;36m START GAME : ./cub3D *.cub [--save] \033[0m"

demo1: all
	@./cub3D maps/barrels.cub

demo2: all
	@/cub3D maps/spaces.cub

clean:
	@rm -f $(OBJ)
	@echo "\033[1;32m OBJECT FILES DELETED \033[0m"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[1;32m EXECUTABLE DELETED \033[0m"

re : fclean all

.PHONY:	all clean fclean re