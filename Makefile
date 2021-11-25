SRCS :=	get_architecture_type.c handle_fat.c \
        help_func.c \
        main.c      \
        nm_parser_x32.c \
        nm_parser_x64.c \
        segment_letter.c


SRC_DIR := ./src

LIB_DIR := ./libft

INC :=	-I ./includes			\
			-I $(LIB_DIR)			\

OBJ_DIR := ./obj

OBJ	:= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

CFLAGS	:= -Wall -Wextra -Werror

LFLAGS	:= -L $(LIB_DIR) -lft

NAME = ft_nm

.PHONY: all clean lib fclean re

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) $(INC) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ) | lib
	gcc -o $(NAME) $(OBJ) $(LFLAGS)

lib:
	make -C $(LIB_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all