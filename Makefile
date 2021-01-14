NAME = maze
MLXDIR = mlx
MLXLIB = libmlx.dylib

CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADER = maze.h
SRC = yellow-square.c
OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@make -C $(MLXDIR)
	@cp $(MLXDIR)/$(MLXLIB) ./
	@$(CC) -g $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "Start a game, good luck! :)"

clean:
	@make -C mlx clean
	@rm $(MLXLIB) $(OBJ) $(NAME)

#fclean: clean

re: clean all

.PHONY: all clean fclean re