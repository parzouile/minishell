
SRCS = main.c start_exe.c here_doc.c find_bin.c command.c aux_exe.c \
		error.c \
		$(PARSING) \
		$(SETUP) \
		$(TOKENS_SRCS) \
		$(ENV) \
		$(DEBUG) \
		$(SIGNALS_SRCS) \
		$(HEREDOC_SRCS) \
		$(BUILTINS_SRCS)

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

SIGNALS_SRCS = signals/signals.c \
				signals/signals_funcs.c

HEREDOC_SRCS = heredoc/expand_heredoc.c

BUILTINS_SRCS = builtins/ft_exit.c \
					builtins/aux_builtins.c \
					builtins/builtins.c