# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 12:13:44 by aschmitt          #+#    #+#              #
#    Updated: 2024/03/21 14:03:02 by aschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

INC				= inc/
SRC_DIR			= src/
OBJ_DIR			= obj/
LIBFT			= libft/libft.a

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 -I $(INC) 
RM				= rm -f

SRC				=	$(SRC_DIR)main.c $(SRC_DIR)parsing.c $(SRC_DIR)test_sleep.c


OBJ 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

B = "\033[94m"
G = "\033[95m"
X = "\033[0m"
R = "\033[31m"

all: 			$(NAME)

bonus:			$(NAME)

$(NAME): 		$(OBJ) $(LIBFT) $(INC)
				@echo $(G)Compiling [$(SRC)]$(X) 
				@$(CC) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
				@echo $(G)Compiling [$(NAME)]$(X) 

$(LIBFT)	:
				@echo $(G)Compiling [LIBFT]$(X) 
				@make -s -C ./libft

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(INC)*.h Makefile
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@echo $(R)delete [$(OBJ)]$(X) 
				@$(RM) -r $(OBJ_DIR)
				@make clean -s -C ./libft

fclean: 		clean
				@echo $(R)delete [$(NAME)]$(X)	
				@$(RM) $(NAME)
				@echo $(R)delete [LIBFT]$(X)
				@make fclean -s -C ./libft

re: 			fclean all

.PHONY: 		all clean fclean re
