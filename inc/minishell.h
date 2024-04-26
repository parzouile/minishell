/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanacze <jbanacze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:12:37 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/26 06:28:05 by jbanacze         ###   ########.fr       */
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

//tokens
t_token	new_token(char *str);
void	free_tokens(t_token tok);
int		push_back(t_token *tok, t_token new);

//setup minishell
int			setup_env(t_env *env, char **envp);
void		free_env(t_env env);
char		*get_value(t_env env, char *str);
t_minishell	create_minishell(char **envp);
void		free_minishell(t_minishell mini);
int			run_minishell(t_minishell mini);

//parsing
char	*expand_str(t_minishell mini, char *str);
int		tokenize(t_token *tok, char *str);

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