/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:38:37 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/15 09:41:16 by aschmitt         ###   ########.fr       */
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

typedef struct s_file
{
	char	*file;
	int		type;
}					t_file;
/*
type :
	1 : >
	2 : >>
	3 : <
	4 : <<
*/

typedef struct s_list_file
{
	t_file	*infile;
	t_file	*outfile;
}					t_list_file;

typedef enum e_type
{
	cmd,
	arg
}	t_type;

typedef struct s_token	*t_token;
typedef struct s_env	*t_env;

struct s_token
{
	char	*str;
	int		type;
	t_token	prev;
	t_token	next;
};

struct s_env
{
	char	*value;
	t_env	next;
};

typedef struct s_minishell
{
	t_token	cmd_line;
	t_env	env;
}	*t_minishell;


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

#endif