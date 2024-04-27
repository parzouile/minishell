/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:12:37 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/27 14:05:41 by jbanacze         ###   ########.fr       */
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

//errors
void		ft_error(char *s);
int			error_msg(char *s);

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

//setup minishell
int			setup_env(t_env *env, char **envp);
int			incr_shlvl(t_env env);

t_minishell	create_minishell(char **envp);
void		free_minishell(t_minishell mini);
int			run_minishell(t_minishell mini);

//parsing
int			is_valid_char(char c);
int			next_dollar_sign(char *str, int *in_dquotes);
char		*lst_to_str(t_list *lst);

char		*expand_str(t_minishell mini, char *str);
int			remove_tokens_quotes(t_token tok);
int			tokenize(t_token *tok, char *str);
t_token		contract_and_move_redirections(t_token tok);
void		put_cmd_types(t_token tok);

int			is_redirection(int type);
int			parse(t_minishell mini, char *str);

//DEBUG
void		print_token(t_token t);
void		print_tenv(t_env env);
void		print_envp(char **envp);

//the rest for now
void		parsing(char **s, char **envp);
void		display_prompt(char **envp);
void		ft_exit(void);
void		ft_pipe(int argc, char **argv, char **envp);
void		command(char *cmd, char **envp);
void		processus(int new_pipe[2], int pipefd[2], char *cmd, char **envp);
char		**find_paths(char **envp, char **args);
int			ft_lentab(char **tab);
void		ft_error(char *s);
void		free_tab(char **path);
char		*ft_join(char *s1, char *s2);
void		ft_ctrlc(int sig);

#endif