/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:12:37 by aschmitt          #+#    #+#             */
/*   Updated: 2024/03/22 11:40:34 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>


void	parsing(char **s, char **envp);
void	display_prompt(char **envp);
void	ft_exit(void);
void	    ft_pipe(int argc, char **argv, char **envp);
void	command(char *cmd, char **envp);
void	processus(int new_pipe[2], int pipefd[2], char *cmd, char **envp);
char	**find_paths(char **envp, char **args);
int     ft_lentab(char **tab);
void	ft_error(char *s);
void	free_tab(char **path);
char	*ft_join(char *s1, char *s2);

#endif