NAME = ft_ssl_md5

CC = cc -Wall -Werror -Wextra -g -Iincludes/

SRCS = srcs/main.c \
		srcs/utils.c \
		srcs/md5.c \
		srcs/sha-256.c \
		srcs/process_hash.c \
		srcs/process_utils.c \
		srcs/whirlpool.c

OBJ_DIR = obj
OBJ = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft/

LIBFT = $(LIBFT_DIR)libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@

$(LIBFT) :
	@make -sC $(LIBFT_DIR) all
	@make -sC $(LIBFT_DIR) bonus

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	@make -sC $(LIBFT_DIR) clean
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -sC $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re