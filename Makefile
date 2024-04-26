NAME				=	minishell

include config/srcs.mk
SRC_PATH			=	src/
DIR_BUILD			=	.build/
OBJS				=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
OBJS_TEST			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(TEST))
DEPS				=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
DEPS_FLAGS			=	-MMD -MP
BASE_CFLAGS			=	-Wall -Werror -Wextra -pipe
BASE_DEBUG_CFLAGS	=	-g3
DEBUG_CLFAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=address
# DEBUG_CLFAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=memory -fsanitize-memory-track-origins
FLAGS				=	$(BASE_CFLAGS)
RM					=	rm -rf
AR					=	ar rcs
CC					=	cc

LIBFT_PATH		=	libft/
LIBFT_INCLUDES	=	$(LIBFT_PATH)
LIBFT_A			=	$(LIBFT_PATH)libft.a
LIBFT_L 		=	$(LIBFT_A)
MAKE_LIBFT		=	$(MAKE) -C $(LIBFT_PATH)

DIR_INCS =\
	inc/			\
	$(LIBFT_INCLUDES)

INCLUDES =\
	$(addprefix -I , $(DIR_INCS))

LIBS = \
		-lreadline \
		$(LIBFT_L)

DEPENDENCIES =\
	$(LIBFT_A)

.PHONY:		all
all:
			$(MAKE_LIBFT)
			$(MAKE) $(NAME)

test:	$(OBJS_TEST)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS_TEST) $(LIBS) -o $(NAME)

$(NAME):	$(OBJS) $(DEPENDENCIES)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)

.PHONY:	clean
clean:
			$(MAKE_LIBFT) clean
			$(RM) $(DIR_BUILD)

.PHONY:	fclean
fclean:	clean
			$(MAKE_LIBFT) fclean
			$(RM) $(NAME)

.PHONY:	debug
debug:
			$(MAKE) -j FLAGS="$(DEBUG_CLFAGS)"

.PHONY:	re
re:		fclean
			$(MAKE) all

.PHONY: valgrind
valgrind:
	$(MAKE) $(NAME)
	valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./$(NAME)
-include $(DEPS)
$(DIR_BUILD)%.o : $(SRC_PATH)%.c Makefile
			@mkdir -p $(shell dirname $@)
			$(CC) $(FLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@
