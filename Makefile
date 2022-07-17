NAME = exec
SRC = \
	main.c \
	exec.c \
	file_descriptors.c \
	redirections.c \
	cmd_search.c \
	builtins.c
OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
FLAGS = -Wall -Werror -Wextra
INC = -I ./ -I ./libft
LIB = -L ./libft -l ft

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

libft/libft.a:
	$(MAKE) -C ./libft

clean:
	rm -rdf $(OBJ_DIR)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all
