/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:12:37 by aschmitt          #+#    #+#             */
/*   Updated: 2024/05/02 19:29:35 by jbanacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"
# include "structures.h"

# define SIG_MAIN 0
# define SIG_FORK 1
# define SIG_HEREDOC 2

extern int	g_current_status;

//errors
int			error_msg(char *s);
void		ft_denied(t_command cmd, t_minishell mini);
void		quit(t_command cmd, t_minishell mini, int n);
void		error_here_doc(char *s);

//tokens
t_token		new_token(char *str);
void		free_token(t_token tok);
void		free_tokens(t_token tok);
int			push_back(t_token *tok, t_token new);

//env
int			add_value(t_env *env, char *str);
void		free_env(t_env env);
t_env		remove_from_env(t_env env, char *key);
char		*get_value(t_env env, char *key);
char		**tenv_to_arr(t_env	env);
t_env		get_node(t_env env, char *key);
int			modify_node_value(t_env env, char *key, char *new_value);

//setup minishell
int			setup_env(t_env *env, char **envp, int top);
int			incr_shlvl(t_env env);

t_minishell	create_minishell(char **envp);
void		free_minishell(t_minishell mini);
int			run_minishell(t_minishell mini);

//parsing
int			double_chevrons(char *str);
int			skip_spaces(char *str);
int			next_special_char(char *str);
int			is_valid_char(char c);
int			is_valid_name(char *str);
int			next_dollar_sign(char *str, int *in_dquotes);
char		*lst_to_str(t_list *lst);
void		treat_quote_expanded(char *s, int restore);

int			value_length(char *str, int in_dquotes);
char		*get_expanded_value(t_minishell mini, char *str, int len_var);
char		*expand_str(t_minishell mini, char *str);
int			remove_tokens_quotes(t_token tok);
int			tokenize(t_token *tok, char *str);
t_token		contract_and_move_redirections(t_token tok);
void		put_cmd_types(t_token tok);

int			is_redirection(int type);
int			parse(t_minishell mini, char *str);

//HEREDOC
char		*expand_heredoc(t_minishell mini, char *str);
int			get_here_doc(char *lim, t_minishell mini, t_command *cmd, int n);

//SIGNALS
void		sig_main_handle(int signal);
void		sig_fork_handle(int signal);
void		sig_heredoc_handle(int signal);
void		assign_sig_handler(int mod);
void		child(int sig);

//DEBUG
void		print_token(t_token t);
void		print_tenv(t_env env);
void		print_envp(char **envp);

//the rest for now
void		parsing(char **s, char **envp);
void		display_prompt(char **envp);
void		ft_pipe(int argc, char **argv, char **envp);
void		command(char *cmd, char **envp);
void		processus(int new_pipe[2], int pipefd[2], char *cmd, char **envp);
int			ft_lentab(char **tab);
void		free_tab(char **path);
char		*ft_join(char *s1, char *s2);
void		ft_ctrlc(int sig);
int			is_builtin(char *s);

// exec
void		start_exe(t_minishell mini);
int			one_builtin(t_minishell mini, t_command command, char **envp);
int			builtin(t_minishell mini, t_command command, char **envp);
char		*find_bin(char *cmd, t_env env);
char		**take_args(t_token *line, t_command *command);
int			redirection(t_command *cmd, t_token *line, t_minishell mini);
pid_t		first_command(t_minishell mini, int pipefd[2]);
int			mid_command(t_minishell mini, int pipefd[2]);
pid_t		last_command(t_minishell mini, int pipefd[2]);
void		end_command(t_command cmd);
pid_t		ft_exec2(t_minishell mini, t_command cmd);
void		zero_command(t_minishell mini);
int			nb_pipe(t_token line);
int			nb_command(t_token line);
void		go_next_pipe(t_minishell mini);
pid_t		ft_exec3(t_minishell mini, t_command command);
pid_t		ft_exec(t_minishell mini, t_command command, int pipefd[2]);
void		one_command(t_minishell mini);

// builtins
void		cut_last_slash(char *str);	
void		ft_echo(t_command command);
void		ft_envp(char **envp);
void		ft_pwd(void);
int			ft_cd(t_command command, t_minishell mini);
int			change_pwd(t_minishell mini);
void		ft_export(t_minishell mini, t_command cmd);
void		ft_unset(t_minishell mini, t_command cmd);
void		ft_exit(t_command cmd, t_minishell mini);
void		error_cd(void);
char		*get_value_cd(t_env env, char *key);

#endif