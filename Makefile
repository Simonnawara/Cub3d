# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 10:34:09 by sinawara          #+#    #+#              #
#    Updated: 2025/03/26 22:11:57 by sinawara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRCS =  main.c \
		parsing/file_check.c

CC = gcc -g -O0
CCFLAG = -Wall -Wextra -Werror
LIB = -C ./libft/

SUCCESS_COLOR = \033[32m

OBJ_DIR = obj

OBJECT = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

D_SRCS = ./src/

# ASCII logo defined as a shell command
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
	@$(CC) $(CCFLAG) -I./libft -I/includes -o $@ -c $<

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJECT)
	@$(LOGO)
	@make $(LIB)
	@$(CC) $(CCFLAG) -o $(NAME) $(OBJECT) -L./libft -lft -lreadline -lhistory
	@echo "$(SUCCESS_COLOR)$(NAME) - Compiled with Success"

clean :
	@make clean $(LIB)
	@echo "$(SUCCESS_COLOR)$(NAME) - Cleaned with Success"
	@/bin/rm -rf $(OBJ_DIR)

fclean : clean
	@make fclean $(LIB)
	@rm -rf ./$(NAME)
	@echo "$(SUCCESS_COLOR)$(NAME) - FCleaned with Success"

re : fclean all

.PHONY: all clean fclean re bonus