# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 12:13:44 by aschmitt          #+#    #+#              #
#    Updated: 2024/02/16 14:04:24 by aschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

INC				= inc/
SRC_DIR			= src/
OBJ_DIR			= obj/
LIBFT			= libft/libft.a

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -I $(INC)
RM				= rm -f

SRC =	$(SRC_DIR)main.c $(SRC_DIR)parsing.c


OBJ 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all: 			$(NAME)

bonus:			$(NAME)

$(NAME): 		$(OBJ) $(LIBFT) $(INC)
				@$(CC) -o $(NAME) $(OBJ) $(LIBFT) 

$(LIBFT)	:
				@make -s -C ./libft

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@$(RM) -r $(OBJ_DIR)
				@make clean -s -C ./libft

fclean: 		clean
				@$(RM) $(NAME)
				@make fclean -s -C ./libft

re: 			fclean all

.PHONY: 		all clean fclean re
