
SRCS = main.c  error.c \
		$(PARSING) \
		$(SETUP) \
		$(TOKENS_SRCS) \
		$(ENV) \
		$(DEBUG) \
		$(SIGNALS_SRCS) \
		$(HEREDOC_SRCS) \
		$(EXEC_SRCS) \
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

HEREDOC_SRCS = heredoc/expand_heredoc.c\
					heredoc/here_doc.c

BUILTINS_SRCS = builtins/ft_exit.c \
					builtins/aux_builtins.c \
					builtins/builtins.c \
					builtins/aux_2_builtins.c \
					builtins/ft_cd.c

EXEC_SRCS = exec/start_exe.c \
				exec/find_bin.c \
				exec/command.c \
				exec/aux_exe.c \
				exec/one_command.c