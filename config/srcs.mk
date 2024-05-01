
SRCS = main.c start_exe.c builtins.c here_doc.c find_bin.c command.c aux_exe.c aux_builtins.c\
		error.c ft_exit.c\
		$(PARSING) \
		$(SETUP) \
		$(TOKENS_SRCS) \
		$(ENV) \
		$(DEBUG) \
		$(SIGNALS_SRCS) \
		$(HEREDOC_SRCS)

PARSING = parsing/tokenize.c \
			parsing/expand_token.c \
			parsing/expand_utils.c \
			parsing/quotes_remover.c \
			parsing/main_parse.c \
			parsing/manage_redirections.c

SETUP = setup/setup.c \
			setup/env_setup.c

ENV = env/env.c \
		env/env2.c

TOKENS_SRCS = manage_tokens/tokens.c

DEBUG = debug/debug_funcs.c

SIGNALS_SRCS = signals/signals.c

HEREDOC_SRCS = heredoc/expand_heredoc.c