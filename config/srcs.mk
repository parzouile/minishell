
SRCS = aux.c \
		command.c \
		main.c \
		parsing.c \
		pipex.c \
		env.c \
		$(PARSING) \
		$(SETUP) \
		$(TOKENS_SRCS)

PARSING = parsing/process_input.c

SETUP = setup/setup.c

TOKENS_SRCS = manage_tokens/tokens.c