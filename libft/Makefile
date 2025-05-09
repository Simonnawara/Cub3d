NAME		=	libft.a
INCLUDES	=	include/
SRC_DIR 	=	src/
OBJ_DIR		=	obj/
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I
RM			=	rm -f
AR			=	ar rcs

#Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

####################
###   SOURCES    ###
####################

FTIS_DIR	=	ft_is/
FTIS		=	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_isspace

FTMEM_DIR	=	ft_mem/
FTMEM		=	ft_bzero ft_calloc ft_memchr ft_memcmp ft_memmove ft_memset

FTPUT_DIR	=	ft_put/
FTPUT		=	ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd

FTTO_DIR	=	ft_to/
FTTO		=	ft_atoi ft_itoa ft_tolower ft_toupper

FTSTR_DIR	=	ft_str/
FTSTR		=	ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
				ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
				ft_strnstr ft_strrchr ft_strtrim ft_substr

FTLST_DIR	=	ft_lst/
FTLST		=	ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
				ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize

FTPRINTF_DIR	=	ft_printf/
FTPRINTF		=	ft_printf ft_putchar ft_putnbr_fd ft_putstr_fd \
					ft_print_hex ft_printcaps_hex ft_unsigned \
					ft_putunsigned ft_pointer ft_hexptr

GET_NEXT_LINE_DIR	=	get_next_line/
GET_NEXT_LINE		=	get_next_line

SRC_FILES+=$(addprefix $(FTIS_DIR),$(FTIS))
SRC_FILES+=$(addprefix $(FTMEM_DIR),$(FTMEM))
SRC_FILES+=$(addprefix $(FTPUT_DIR),$(FTPUT))
SRC_FILES+=$(addprefix $(FTTO_DIR),$(FTTO))
SRC_FILES+=$(addprefix $(FTSTR_DIR),$(FTSTR))
SRC_FILES+=$(addprefix $(FTPRINTF_DIR),$(FTPRINTF))
SRC_FILES+=$(addprefix $(GET_NEXT_LINE_DIR),$(GET_NEXT_LINE))
BONUS_FILES+=$(addprefix $(FTLST_DIR),$(FTLST))

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
BONUS_OBJ	= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(BONUS_FILES)))

###

OBJF		=	.cache_exists

# Make sure SRCS is correctly defined
TOTAL_FILES := $(words $(SRC) $(addprefix $(SRC_DIR), $(addsuffix .c, $(BONUS_FILES))))
COMPILED_FILES = 0

define progress_bar
    @$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES) + 1))))
    @if [ $(TOTAL_FILES) -gt 0 ]; then \
        PROGRESS=$$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES))); \
        BAR=$$(seq -s= $$(($$PROGRESS / 5)) | sed 's/[0-9]//g'); \
        printf "\rCompiling project[%-20s] %d%%" $$BAR $$PROGRESS; \
    fi
endef

all: $(NAME)

$(NAME):	$(OBJ) $(BONUS_OBJ)
			@$(AR) $(NAME) $(OBJ) $(BONUS_OBJ)
			@echo "$(GREEN)\nlibft - Compiled with Success$(DEF_COLOR)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
			$(call progress_bar)

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(FTIS_DIR)
			@mkdir -p $(OBJ_DIR)$(FTMEM_DIR)
			@mkdir -p $(OBJ_DIR)$(FTPUT_DIR)
			@mkdir -p $(OBJ_DIR)$(FTTO_DIR)
			@mkdir -p $(OBJ_DIR)$(FTSTR_DIR)
			@mkdir -p $(OBJ_DIR)$(FTLST_DIR)
			@mkdir -p $(OBJ_DIR)$(FTPRINTF_DIR)
			@mkdir -p $(OBJ_DIR)$(GET_NEXT_LINE_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@$(RM) -f $(OBJF)
			@echo "$(BLUE)Libft objects files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@echo "$(CYAN)Libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

.PHONY:		all clean fclean re