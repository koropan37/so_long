# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 16:16:52 by skimura           #+#    #+#              #
#    Updated: 2025/07/07 18:46:53 by skimura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

MLX_DIR = /home/skimura/minilibx-linux
LIBFT_DIR = /home/skimura/mylibft

SRCS = src/main.c \
       src/collectable.c \
       src/read_xpm.c \
       src/read_map.c \
	   src/read_map_utils.c \
       src/close.c \
       src/enemy.c \
	   src/player.c \
	   src/set_map.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I$(LIBFT_DIR)/include
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd -lm
LIBFT = $(LIBFT_DIR)/libft.a
RM			= rm -f
MAKEFLAGS 	+= --no-print-directory

RESET   = \033[0m
BOLD    = \033[1m
BLACK   = \033[0;30m
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
WHITE   = \033[0;37m

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_DIR)/libmlx.a $(OBJS)
	@echo  "$(BOLD)$(GREEN)[INFO]$(CYAN) Building $(WHITE)$(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)[OK]$(BLUE) Build completed!$(RESET)"

%.o: %.c so_long.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	@make -C $(MLX_DIR)

clean:
	@echo  "$(BOLD)$(YELLOW)[INFO]$(MAGENTA) cleaning $(NAME)..."
	$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "$(RED)[DONE]$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(BOLD)$(YELLOW)[DELETE]$(RED)All clean $(NAME)$(RESET)"

re: fclean all

.PHONY: all clean fclean re
