# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mjiam <mjiam@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/09/20 17:03:06 by mjiam         #+#    #+#                  #
#    Updated: 2021/09/29 18:01:00 by mjiam         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

HEADER	=	philo.h

CC		=	gcc

FLAGS	= 	-Wall -Wextra -Werror $(INC)

ifdef DEBUG
FLAGS	+=	-fsanitize=address -fno-omit-frame-pointer -g
endif

ifeq ($(OS),Linux)
	INC	=	-I $(INC_DIR) -lpthread
else
	INC	= 	-I $(INC_DIR)
endif

SRC		=	check.c exit.c fork.c init.c main.c message.c philo.c \
			philo_utils.c prog_utils.c setup.c time.c

OBJ		=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# DIRECTORIES
SRC_DIR		=	src
INC_DIR		=	inc
OBJ_DIR		=	obj

# COLORS
CYAN		= 	\033[0;36m
PURPLE		= 	\033[0;35m
BLUE		= 	\033[0;34m
GREEN		= 	\033[0;32m
RESET		= 	\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(INC) -o $@
	@echo "Executable $(CYAN)$@$(RESET) made"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(PURPLE)Compiling: $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

# makes obj directory order-only prereq so no targets are rebuilt
# if directory timestamp changes
$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

debug:
	@echo "$(GREEN)Debug mode$(RESET)"
	@$(MAKE) DEBUG=1

clean:
	@echo "$(BLUE)Cleaning$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Removed: $(OBJ_DIR) folder$(RESET)"

fclean: clean
	@echo "$(BLUE)Removing: $(NAME)$(RESET)"
	@rm -rf $(NAME)
	@echo "$(BLUE)Clean af$(RESET)"

re:
	@echo "$(BLUE)Once more from the top$(RESET)"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
