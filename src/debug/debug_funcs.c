/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:12:57 by jules             #+#    #+#             */
/*   Updated: 2024/04/26 23:58:10 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_type(int t)
{
	switch (t)
	{
		case ARG:
			printf("ARG");
			break ;
		case PIPE:
			printf("PIPE");
			break ;
		case INFILE:
			printf("INFILE");
			break ;
		case OUTFILE:
			printf("OUTFILE");
			break ;
		case OUTFILE_APPEND:
			printf("OUTFILE_APPEND");
			break ;
		case INFILE_HEREDOC:
			printf("INFILE_HEREDOC");
			break ;
		default:
			printf("NON RECONNU");
	}
}

void print_token(t_token t)
{
	if (!t)
		return ;
	printf("TYPE : ");
	print_type(t->type);
	printf("\n");
	if (t->str)
		printf("STR : %s\\n\n\n", t->str);
	print_token(t->next);
}

void	print_tenv(t_env env)
{
	if (!env)
		return ;
	printf("%s=%s\n", env->name, env->value);
	print_tenv(env->next);
}

void	print_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}
