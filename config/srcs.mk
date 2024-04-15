
SRCS = aux.c \
		command.c \
		main.c \
		parsing.c \
		pipex.c \
		startexe.c \
		$(PARSING) \
		$(SETUP)

PARSING = parsing/process_input.c

SETUP = setup/setup.c