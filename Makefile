# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 10:34:09 by sinawara          #+#    #+#              #
#    Updated: 2025/03/29 15:35:47 by trouilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRCS =  main.c \
		parsing/file_check.c \
		parsing/check_map.c \
		parsing/free.c \
		parsing/parse_map.c \
		parsing/color_check.c \
		init.c \
		cleanup.c \
		raycasting.c \
		move.c \
		time.c \
		minimap.c \
		game_loop.c

CC = gcc -g -O0
CCFLAG = -Wall -Wextra -Werror

OBJ_DIR = obj
D_SRCS = ./src/
OBJECT = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# === LIBRARIES ===
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux

INCLUDES = -I$(LIBFT_DIR) -I$(MLX_DIR) -Iincludes

LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lreadline -lhistory -lX11 -lXext -lm -lz

SUCCESS_COLOR = \033[32m

# === ASCII LOGO ===
WHITE   = \033[37m
RED     = \033[31m
BURGUNDY = \033[38;5;88m
BLUE    = \033[34m
GREEN   = \033[32m
MINECRAFT_GREEN = \033[38;5;70m
YELLOW  = \033[33m
PINK    = \033[35m
CYAN    = \033[36m
ORANGE  = \033[38;5;214m
PURPLE  = \033[38;5;93m

LOGO = printf "\n\
$(MINECRAFT_GREEN) ██████╗██╗   ██╗██████╗  ██████╗ ██████╗ $(MINECRAFT_GREEN)\n\
$(MINECRAFT_GREEN)██╔════╝██║   ██║██╔══██╗ ╚════██╗██╔══██╗$(MINECRAFT_GREEN)\n\
$(MINECRAFT_GREEN)██║     ██║   ██║██████╔╝  █████╔╝██║  ██║$(MINECRAFT_GREEN)\n\
$(MINECRAFT_GREEN)██║     ██║   ██║██╔══██╗  ╚═══██╗██║  ██║$(MINECRAFT_GREEN)\n\
$(MINECRAFT_GREEN)╚██████╗╚██████╔╝██████╔╝ ██████╔╝██████╔╝$(MINECRAFT_GREEN)\n\
$(MINECRAFT_GREEN) ╚═════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═════╝ $(MINECRAFT_GREEN)\n"

all :  $(NAME)

$(OBJ_DIR)/%.o: $(D_SRCS)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAG) $(INCLUDES) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJECT)
	@$(LOGO)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	@$(CC) $(CCFLAG) -o $(NAME) $(OBJECT) $(LIBS)
	@echo "$(SUCCESS_COLOR)$(NAME) - Compiled with Success"

clean :
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(SUCCESS_COLOR)$(NAME) - Cleaned with Success"

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@rm -rf ./$(NAME)
	@echo "$(SUCCESS_COLOR)$(NAME) - FCleaned with Success"

re : fclean all

.PHONY: all clean fclean re bonus
