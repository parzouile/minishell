
SRCS = aux.c \
		command.c \
		main.c \
		parsing.c \
		pipex.c \
		env.c \
		$(PARSING) \
		$(SETUP)

PARSING = parsing/process_input.c

SETUP = setup/setup.c