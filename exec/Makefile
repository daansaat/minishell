NAME = exec
SRC_DIR = src/
SRC = \
	main.c \
	exec.c
OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
FLAGS = -Wall -Werror -Wextra
INC = -I ./inc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	rm -rdf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# NAME = exec
# SRC = \
# 	exec.c \
# 	main.c
# OBJ = $(SRCS:.c=.o)
# FLAGS = -Wall -Werror -Wextra
# INC = exec.h

# all: $(NAME)

# $(NAME): $(OBJ) 
# 	$(CC) $(FLAGS) $(INC) $(SRCS) -o $(NAME)

# %.o: %.c
# 	$(CC) -c $(INC) $< -o $@

# clean:
# 	rm -f $(OBJS)

# fclean: clean
# 	rm -f $(NAME)

# re: clean fclean all