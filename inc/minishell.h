/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:38:37 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/26 17:21:19 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structures.h"
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


//setup minishell
int			setup_env(t_env *env, char **envp);
void		free_env(t_env env);
t_minishell	create_minishell(char **envp);
void		free_minishell(t_minishell mini);
int			run_minishell(t_minishell mini);

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
void		free_tab(char **path);
void		processus(int new_pipe[2], int pipefd[2], char *cmd, char **envp);
void		start_exe(t_minishell mini);
char		**tenv_to_arr(t_env	env);
int			get_here_doc(char *limiter);
int			find_file(t_command *cmd, t_token *line);
char		**take_args(t_token *line);
int			one_builtin(t_minishell mini, t_command command, char **envp);
int			builtin(t_minishell mini, t_command command, int pipefd[2], char **envp);

#endif