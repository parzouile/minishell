/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:38:06 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/30 10:38:11 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define CMD 1
# define ARG 2
# define INFILE 3
# define INFILE_HEREDOC 4
# define OUTFILE 5
# define OUTFILE_APPEND 6
# define PIPE 7

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
	char	*name;
	char	*value;
	t_env	next;
};

typedef struct s_minishell
{
	t_token	cmd_line;
	t_env	env;
	int		exit;
	char	**envp;
}	*t_minishell;

typedef struct s_command
{
	char	*cmd;
	char	**args;
	int		infile;
	int		outfile;
}					t_command;

#endif